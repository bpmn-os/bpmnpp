#include "Model.h"
#include "xml/bpmn/tLinkEventDefinition.h"
#include "xml/bpmn/tCancelEventDefinition.h"
#include "xml/bpmn/tCompensateEventDefinition.h"
#include "xml/bpmn/tConditionalEventDefinition.h"
#include "xml/bpmn/tErrorEventDefinition.h"
#include "xml/bpmn/tEscalationEventDefinition.h"
#include "xml/bpmn/tMessageEventDefinition.h"
#include "xml/bpmn/tSignalEventDefinition.h"
#include "xml/bpmn/tTimerEventDefinition.h"
#include "xml/bpmn/tTerminateEventDefinition.h"
#include "xml/bpmn/tCollaboration.h"
#include "xml/bpmn/tParticipant.h"
#include "xml/bpmn/tAssociation.h"

using namespace BPMN;

Model::Model(const std::string& filename)
{
  readBPMNFile(filename);
}

void Model::readBPMNFile(const std::string& filename)
{
  roots.push_back( std::unique_ptr<XML::XMLObject>(XML::XMLObject::createFromFile(filename)) );

  for ( XML::bpmn::tProcess& process : (*roots.rbegin())->getChildren<XML::bpmn::tProcess>() ) {
    processes.push_back(createProcess(&process));
  }
  
  for ( auto& process : processes ) {
    createChildNodes(process.get());
    createSequenceFlows(process.get());
    createNestedReferences(process.get());
    createCompensations(process.get());
  }

  createMessageFlows();
  for ( auto& process : processes ) {
    createLinks(process.get());
  }
}

std::unique_ptr<Process> Model::createProcess(XML::bpmn::tProcess* process) {
  return std::make_unique<Process>(process);
}

std::unique_ptr<EventSubProcess> Model::createEventSubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent) {
  return std::make_unique<EventSubProcess>(subProcess,parent);
}

std::unique_ptr<FlowNode> Model::createFlowNode(XML::bpmn::tFlowNode* flowNode, Scope* parent) {
  if ( auto activity = flowNode->is<XML::bpmn::tActivity>(); activity ) {
    return createActivity(activity,parent);
  }
  else if ( auto event = flowNode->is<XML::bpmn::tEvent>(); event ) {
    return createEvent(event,parent);
  }
  else if ( auto gateway = flowNode->is<XML::bpmn::tGateway>(); gateway ) {
    return createGateway(gateway,parent);
  }
  else {
    throw std::logic_error("Model: Flow node is neither activity, event, nor gateway");
  }

  return nullptr;
}

std::unique_ptr<FlowNode> Model::createActivity(XML::bpmn::tActivity* activity, Scope* parent) {
  if ( auto subProcess = activity->is<XML::bpmn::tSubProcess>(); subProcess ) {
    return createSubProcess(subProcess,parent);
  }
  if ( auto callActivity = activity->is<XML::bpmn::tCallActivity>(); callActivity ) {
    return createCallActivity(callActivity,parent);
  }
  if ( auto task = activity->is<XML::bpmn::tTask>(); task ) {
    return createTask(task,parent);
  }
  else {
    throw std::logic_error("Model: Activity is neither subprocess, call activity, nor task");
  }

  return nullptr;
}

std::unique_ptr<FlowNode> Model::createSubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent) {
  if ( auto adHocSubProcess = subProcess->is<XML::bpmn::tAdHocSubProcess>(); adHocSubProcess ) {
    return createAdHocSubProcess(adHocSubProcess,parent);
  }
  else if ( auto transaction = subProcess->is<XML::bpmn::tTransaction>(); transaction ) {
    return createTransaction(transaction,parent);
  }
  return std::make_unique<SubProcess>(subProcess,parent);
}

std::unique_ptr<FlowNode> Model::createAdHocSubProcess(XML::bpmn::tAdHocSubProcess* adHocSubProcess, Scope* parent) {
  return std::make_unique<AdHocSubProcess>(adHocSubProcess,parent);
}

std::unique_ptr<FlowNode> Model::createTransaction(XML::bpmn::tTransaction* transaction, Scope* parent) {
  return std::make_unique<Transaction>(transaction,parent);
}

std::unique_ptr<FlowNode> Model::createCallActivity(XML::bpmn::tCallActivity* callActivity, Scope* parent) {
  return std::make_unique<CallActivity>(callActivity,parent);
}

std::unique_ptr<FlowNode> Model::createTask(XML::bpmn::tTask* task, Scope* parent) {
  if ( auto sendTask = task->is<XML::bpmn::tSendTask>(); sendTask ) {
    return std::make_unique<SendTask>(sendTask,parent);
  }
  else if ( auto receiveTask = task->is<XML::bpmn::tReceiveTask>(); receiveTask ) {
    return std::make_unique<ReceiveTask>(receiveTask,parent);
  }
  else if ( auto userTask = task->is<XML::bpmn::tUserTask>(); userTask ) {
    return std::make_unique<UserTask>(userTask,parent);
  }
  else if ( auto manualTask = task->is<XML::bpmn::tManualTask>(); manualTask ) {
    return std::make_unique<ManualTask>(manualTask,parent);
  }
  else if ( auto scriptTask = task->is<XML::bpmn::tScriptTask>(); scriptTask ) {
    return std::make_unique<ScriptTask>(scriptTask,parent);
  }
  else if ( auto businessRuleTask = task->is<XML::bpmn::tBusinessRuleTask>(); businessRuleTask ) {
    return std::make_unique<BusinessRuleTask>(businessRuleTask,parent);
  }

  return createUntypedTask(task,parent);
}

std::unique_ptr<FlowNode> Model::createUntypedTask(XML::bpmn::tTask* task, Scope* parent) {
  return std::make_unique<UntypedTask>(task,parent);
}

std::unique_ptr<FlowNode> Model::createSendTask(XML::bpmn::tSendTask* sendTask, Scope* parent) {
  return std::make_unique<SendTask>(sendTask,parent);
}

std::unique_ptr<FlowNode> Model::createReceiveTask(XML::bpmn::tReceiveTask* receiveTask, Scope* parent) {
  return std::make_unique<ReceiveTask>(receiveTask,parent);
}

std::unique_ptr<FlowNode> Model::createUserTask(XML::bpmn::tUserTask* userTask, Scope* parent) {
  return std::make_unique<UserTask>(userTask,parent);
}

std::unique_ptr<FlowNode> Model::createManualTask(XML::bpmn::tManualTask* manualTask, Scope* parent) {
  return std::make_unique<ManualTask>(manualTask,parent);
}

std::unique_ptr<FlowNode> Model::createScriptTask(XML::bpmn::tScriptTask* scriptTask, Scope* parent) {
  return std::make_unique<ScriptTask>(scriptTask,parent);
}

std::unique_ptr<FlowNode> Model::createBusinessRuleTask(XML::bpmn::tBusinessRuleTask* businessRuleTask, Scope* parent) {
  return std::make_unique<BusinessRuleTask>(businessRuleTask,parent);
}

std::unique_ptr<FlowNode> Model::createEvent(XML::bpmn::tEvent* event, Scope* parent) {
  if ( auto boundaryEvent = event->is<XML::bpmn::tBoundaryEvent>(); boundaryEvent ) {
    return createBoundaryEvent(boundaryEvent,parent);
  }
  else if ( auto catchEvent = event->is<XML::bpmn::tCatchEvent>(); catchEvent ) {
    return createCatchEvent(catchEvent,parent);
  }
  else if ( auto throwEvent = event->is<XML::bpmn::tThrowEvent>(); throwEvent ) {
    return createThrowEvent(throwEvent,parent);
  }
  else {
    throw std::logic_error("Model: Event is neither boundary, catch, nor throw event");
  }

  return nullptr;
}

std::unique_ptr<FlowNode> Model::createBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent) {
  auto eventDefinitions = boundaryEvent->getChildren<XML::bpmn::tEventDefinition>();
  if ( eventDefinitions.empty() ) {
    throw std::runtime_error("Model: Boundary event '" + boundaryEvent->id.value().get().value.value + "' has no event definition");
  }
  else if ( eventDefinitions.size() > 1 ) {
    throw std::runtime_error("Model: Multiple event definitions are not yet supported");
  }

  if ( eventDefinitions[0].get().is<XML::bpmn::tCancelEventDefinition>() ) {
    return createCancelBoundaryEvent(boundaryEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tCompensateEventDefinition>() ) {
    return createCompensateBoundaryEvent(boundaryEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tConditionalEventDefinition>() ) {
    return createConditionalBoundaryEvent(boundaryEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tErrorEventDefinition>() ) {
    return createErrorBoundaryEvent(boundaryEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tEscalationEventDefinition>() ) {
    return createEscalationBoundaryEvent(boundaryEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tMessageEventDefinition>() ) {
    return createMessageBoundaryEvent(boundaryEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tSignalEventDefinition>() ) {
    return createSignalBoundaryEvent(boundaryEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tTimerEventDefinition>() ) {
    return createTimerBoundaryEvent(boundaryEvent,parent);
  }
  
  throw std::logic_error("Model: Failed determining event definition for boundary event '" + boundaryEvent->id.value().get().value.value + "'");

  return nullptr;
}

std::unique_ptr<FlowNode> Model::createCancelBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent) {
  return std::make_unique<CancelBoundaryEvent>(boundaryEvent,parent);
}

std::unique_ptr<FlowNode> Model::createCompensateBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent) {
  return std::make_unique<CompensateBoundaryEvent>(boundaryEvent,parent);
}

std::unique_ptr<FlowNode> Model::createConditionalBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent) {
  return std::make_unique<ConditionalBoundaryEvent>(boundaryEvent,parent);
}

std::unique_ptr<FlowNode> Model::createErrorBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent) {
  return std::make_unique<ErrorBoundaryEvent>(boundaryEvent,parent);
}

std::unique_ptr<FlowNode> Model::createEscalationBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent) {
  return std::make_unique<EscalationBoundaryEvent>(boundaryEvent,parent);
}

std::unique_ptr<FlowNode> Model::createMessageBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent) {
  return std::make_unique<MessageBoundaryEvent>(boundaryEvent,parent);
}

std::unique_ptr<FlowNode> Model::createSignalBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent) {
  return std::make_unique<SignalBoundaryEvent>(boundaryEvent,parent);
}

std::unique_ptr<FlowNode> Model::createTimerBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent) {
  return std::make_unique<TimerBoundaryEvent>(boundaryEvent,parent);
}

std::unique_ptr<FlowNode> Model::createCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  auto eventDefinitions = catchEvent->getChildren<XML::bpmn::tEventDefinition>();
  if ( eventDefinitions.empty() ) {
    return createUntypedStartEvent(catchEvent,parent);
  }
  else if ( eventDefinitions.size() > 1 ) {
    throw std::runtime_error("Model: Multiple event definitions are not yet supported");
  }

  if ( auto startEvent = catchEvent->is<XML::bpmn::tStartEvent>(); startEvent ) {
    return createTypedStartEvent(startEvent,eventDefinitions[0].get(),parent);
  }

  if ( eventDefinitions[0].get().is<XML::bpmn::tConditionalEventDefinition>() ) {
    return createConditionalCatchEvent(catchEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tMessageEventDefinition>() ) {
    return createMessageCatchEvent(catchEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tSignalEventDefinition>() ) {
    return createSignalCatchEvent(catchEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tTimerEventDefinition>() ) {
    return createTimerCatchEvent(catchEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tLinkEventDefinition>() ) {
    return createLinkTargetEvent(catchEvent,parent);
  }

  throw std::logic_error("Model: Failed determining event definition for catching event '" + catchEvent->id.value().get().value.value + "'");

  return nullptr;
}

std::unique_ptr<FlowNode> Model::createConditionalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  return std::make_unique<ConditionalCatchEvent>(catchEvent,parent);
}


std::unique_ptr<FlowNode> Model::createMessageCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  return std::make_unique<MessageCatchEvent>(catchEvent,parent);
}

std::unique_ptr<FlowNode> Model::createSignalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  return std::make_unique<SignalCatchEvent>(catchEvent,parent);
}

std::unique_ptr<FlowNode> Model::createTimerCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  return std::make_unique<TimerCatchEvent>(catchEvent,parent);
}

std::unique_ptr<FlowNode> Model::createLinkTargetEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  return std::make_unique<LinkTargetEvent>(catchEvent,parent);
}

std::unique_ptr<FlowNode> Model::createTypedStartEvent(XML::bpmn::tStartEvent* startEvent, XML::bpmn::tEventDefinition& eventDefinition, Scope* parent) {
  if ( eventDefinition.is<XML::bpmn::tCompensateEventDefinition>() ) {
    return createCompensateStartEvent(startEvent,parent);
  }
  else if ( eventDefinition.is<XML::bpmn::tErrorEventDefinition>() ) {
    return createErrorStartEvent(startEvent,parent);
  }
  else if ( eventDefinition.is<XML::bpmn::tEscalationEventDefinition>() ) {
    return createEscalationStartEvent(startEvent,parent);
  }
  else if ( eventDefinition.is<XML::bpmn::tConditionalEventDefinition>() ) {
    return createConditionalStartEvent(startEvent,parent);
  }
  else if ( eventDefinition.is<XML::bpmn::tMessageEventDefinition>() ) {
    return createMessageStartEvent(startEvent,parent);
  }
  else if ( eventDefinition.is<XML::bpmn::tSignalEventDefinition>() ) {
    return createSignalStartEvent(startEvent,parent);
  }
  else if ( eventDefinition.is<XML::bpmn::tTimerEventDefinition>() ) {
    return createTimerStartEvent(startEvent,parent);
  }

  throw std::logic_error("Model: Failed determining event definition for typed start event '" + startEvent->id.value().get().value.value + "'");

  return nullptr;
}

std::unique_ptr<FlowNode> Model::createCompensateStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent) {
  return std::make_unique<CompensateStartEvent>(startEvent,parent);
}

std::unique_ptr<FlowNode> Model::createErrorStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent) {
  return std::make_unique<ErrorStartEvent>(startEvent,parent);
}

std::unique_ptr<FlowNode> Model::createEscalationStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent) {
  return std::make_unique<EscalationStartEvent>(startEvent,parent);
}

std::unique_ptr<FlowNode> Model::createConditionalStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent) {
  return std::make_unique<ConditionalStartEvent>(startEvent,parent);
}

std::unique_ptr<FlowNode> Model::createMessageStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent) {
  return std::make_unique<MessageStartEvent>(startEvent,parent);
}

std::unique_ptr<FlowNode> Model::createSignalStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent) {
  return std::make_unique<SignalStartEvent>(startEvent,parent);
}

std::unique_ptr<FlowNode> Model::createTimerStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent) {
  return std::make_unique<TimerStartEvent>(startEvent,parent);
}

std::unique_ptr<FlowNode> Model::createUntypedStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  return std::make_unique<UntypedStartEvent>(catchEvent,parent);
}

std::unique_ptr<FlowNode> Model::createThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent) {
  auto eventDefinitions = throwEvent->getChildren<XML::bpmn::tEventDefinition>();
  if ( eventDefinitions.empty() ) {
    return createUntypedEndEvent(throwEvent,parent);
  }
  else if ( eventDefinitions.size() > 1 ) {
    throw std::runtime_error("Model: Multiple event definitions are not yet supported");
  }

  if ( eventDefinitions[0].get().is<XML::bpmn::tCancelEventDefinition>() ) {
    return createCancelEndEvent(throwEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tCompensateEventDefinition>() ) {
    return createCompensateThrowEvent(throwEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tErrorEventDefinition>() ) {
    return createErrorEndEvent(throwEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tEscalationEventDefinition>() ) {
    return createEscalationThrowEvent(throwEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tMessageEventDefinition>() ) {
    return createMessageThrowEvent(throwEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tSignalEventDefinition>() ) {
    return createSignalThrowEvent(throwEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tTerminateEventDefinition>() ) {
    return createTerminateEvent(throwEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tLinkEventDefinition>() ) {
    return createLinkSourceEvent(throwEvent,parent);
  }

  throw std::logic_error("Model: Failed determining event definition for throwing event '" + throwEvent->id.value().get().value.value + "'");

  return nullptr;
}

std::unique_ptr<FlowNode> Model::createCancelEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent) {
  return std::make_unique<CancelEndEvent>(throwEvent,parent);
}

std::unique_ptr<FlowNode> Model::createCompensateThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent) {
  return std::make_unique<CompensateThrowEvent>(throwEvent,parent);
}

std::unique_ptr<FlowNode> Model::createErrorEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent) {
  return std::make_unique<ErrorEndEvent>(throwEvent,parent);
}

std::unique_ptr<FlowNode> Model::createEscalationThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent) {
  return std::make_unique<EscalationThrowEvent>(throwEvent,parent);
}

std::unique_ptr<FlowNode> Model::createMessageThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent) {
  return std::make_unique<MessageThrowEvent>(throwEvent,parent);
}

std::unique_ptr<FlowNode> Model::createSignalThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent) {
  return std::make_unique<SignalThrowEvent>(throwEvent,parent);
}

std::unique_ptr<FlowNode> Model::createTerminateEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent) {
  return std::make_unique<TerminateEvent>(throwEvent,parent);
}

std::unique_ptr<FlowNode> Model::createLinkSourceEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent) {
  return std::make_unique<LinkSourceEvent>(throwEvent,parent);
}

std::unique_ptr<FlowNode> Model::createUntypedEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent) {
  return std::make_unique<UntypedEndEvent>(throwEvent,parent);
}


std::unique_ptr<FlowNode> Model::createGateway(XML::bpmn::tGateway* gateway, Scope* parent) {
  if ( auto parallelGateway = gateway->is<XML::bpmn::tParallelGateway>(); parallelGateway ) {
    return createParallelGateway(parallelGateway,parent);
  }
  else if ( auto exclusiveGateway = gateway->is<XML::bpmn::tExclusiveGateway>(); exclusiveGateway ) {
    return createExclusiveGateway(exclusiveGateway,parent);
  }
  else if ( auto inclusiveGateway = gateway->is<XML::bpmn::tInclusiveGateway>(); inclusiveGateway ) {
    return createInclusiveGateway(inclusiveGateway,parent);
  }
  else if ( auto complexGateway = gateway->is<XML::bpmn::tComplexGateway>(); complexGateway ) {
    return createComplexGateway(complexGateway,parent);
  }
  else if ( auto eventBasedGateway = gateway->is<XML::bpmn::tEventBasedGateway>(); eventBasedGateway ) {
    return createEventBasedGateway(eventBasedGateway,parent);
  }
  else {
    throw std::logic_error("Model: Gateway '" + gateway->id.value().get().value.value + "' is neither parallel, exclusive, inclusive, complex, nor event-based gateway");
  }

  return nullptr;
}

std::unique_ptr<FlowNode> Model::createParallelGateway(XML::bpmn::tParallelGateway* parallelGateway, Scope* parent) {
  return std::make_unique<ParallelGateway>(parallelGateway,parent);
}

std::unique_ptr<FlowNode> Model::createExclusiveGateway(XML::bpmn::tExclusiveGateway* exclusiveGateway, Scope* parent) {
  return std::make_unique<ExclusiveGateway>(exclusiveGateway,parent);
}

std::unique_ptr<FlowNode> Model::createInclusiveGateway(XML::bpmn::tInclusiveGateway* inclusiveGateway, Scope* parent) {
  return std::make_unique<InclusiveGateway>(inclusiveGateway,parent);
}

std::unique_ptr<FlowNode> Model::createEventBasedGateway(XML::bpmn::tEventBasedGateway* eventBasedGateway, Scope* parent) {
  return std::make_unique<EventBasedGateway>(eventBasedGateway,parent);
}

std::unique_ptr<FlowNode> Model::createComplexGateway(XML::bpmn::tComplexGateway* complexGateway, Scope* parent) {
  return std::make_unique<ComplexGateway>(complexGateway,parent);
}

std::unique_ptr<SequenceFlow> Model::createSequenceFlow(XML::bpmn::tSequenceFlow* sequenceFlow, Scope* scope) {
  return std::make_unique<SequenceFlow>(sequenceFlow,scope);
}

std::unique_ptr<MessageFlow> Model::createMessageFlow(XML::bpmn::tMessageFlow* messageFlow) {
  return std::make_unique<MessageFlow>(messageFlow);
}

void Model::createChildNodes(Scope* scope) {
  // add flow nodes (except boundary events)
  for (XML::bpmn::tFlowNode& flowNode : scope->element->getChildren<XML::bpmn::tFlowNode>() ) {
    if ( auto subProcess = flowNode.is<XML::bpmn::tSubProcess>();
         subProcess &&
         subProcess->triggeredByEvent.has_value() &&
         (bool)subProcess->triggeredByEvent->get().value
    ) {
      scope->add(createEventSubProcess(subProcess,scope));
    }
    else if ( !flowNode.is<XML::bpmn::tBoundaryEvent>() ) {
      // create node according to element type
      scope->add(createFlowNode(&flowNode,scope));
    }
  }
  // add boundary events
  for (XML::bpmn::tFlowNode& flowNode: scope->element->getChildren<XML::bpmn::tFlowNode>() ) {
    if ( auto boundaryEvent = flowNode.is<XML::bpmn::tBoundaryEvent>(); boundaryEvent ) {
      scope->add(createBoundaryEvent(boundaryEvent,scope));
    }
  }
  // recurse
  for ( auto& childNode: scope->childNodes ) {
    if ( auto childScope = childNode->represents<Scope>(); childScope ) {
      createChildNodes(childScope);
      createSequenceFlows(childScope);
    }
  }
}

void Model::createSequenceFlows(Scope* scope) {
  // add sequence flows within scope of the node
  for (XML::bpmn::tSequenceFlow& sequenceFlow: scope->element->getChildren<XML::bpmn::tSequenceFlow>() ) {
    scope->add(createSequenceFlow(&sequenceFlow,scope));
  }
  // recurse
  for ( auto& childNode: scope->childNodes ) {
    if ( auto scope = childNode->represents<Scope>(); scope ) {
      createSequenceFlows(scope);
    }
  }
}

void Model::createNestedReferences(Scope* scope) {
  for ( auto flowNode: scope->flowNodes ) {
    createFlowReferences(flowNode);
  }
  for ( auto eventSubProcess: scope->eventSubProcesses ) {
    createNestedReferences(eventSubProcess);
  }
}

void Model::createFlowReferences(FlowNode* flowNode) {
  if ( flowNode->parent ) {
    // link incoming sequence flows
    for ( auto& inflow : flowNode->element->incoming ) {
      for (auto& sequenceFlow : flowNode->parent->sequenceFlows ) {
        if ( sequenceFlow->id.size() && inflow.get().textContent == sequenceFlow->id ) {
          flowNode->incoming.push_back(sequenceFlow.get());
          break;
        }
      }
    }
   
    // add to start nodes of parent if required 
    if ( auto untypedStartEvent = flowNode->represents<UntypedStartEvent>() ) {
      flowNode->parent->startEvents.push_back(untypedStartEvent);
      if ( auto subProcess = untypedStartEvent->parent->represents<SubProcess>() ) {
        if ( subProcess->startEvent ) {
          throw std::runtime_error("Model: more than one start event provided for '" + subProcess->id + "'");
        }
        subProcess->startEvent = untypedStartEvent;
      }
      else if ( untypedStartEvent->parent->represents<EventSubProcess>() ) { 
        throw std::runtime_error("Model: untyped start event provided for event subprocess '" + untypedStartEvent->parent->id + "'");
      }
    }
    else if ( auto typedStartEvent = flowNode->represents<TypedStartEvent>() ) {
      flowNode->parent->startEvents.push_back(typedStartEvent);
      if ( auto eventSubProcess = typedStartEvent->parent->represents<EventSubProcess>() ) {
        if ( eventSubProcess->startEvent ) {
          throw std::runtime_error("Model: more than one start event provided for '" + eventSubProcess->id + "'");
        }
        eventSubProcess->startEvent = typedStartEvent;
        if ( typedStartEvent->represents<CompensateStartEvent>() ) {
          if ( eventSubProcess->parent->compensationEventSubProcess ) {
            throw std::runtime_error("Model: more than one compensation event subprocess provided for '" + eventSubProcess->parent->id + "'");
          }
          eventSubProcess->parent->compensationEventSubProcess = eventSubProcess;
        }
      }
      else if ( typedStartEvent->parent->represents<SubProcess>() ) {
        throw std::runtime_error("Model: typed start event provided for subprocess '" + typedStartEvent->parent->id + "'");
      }
      else if ( typedStartEvent->parent->represents<Process>() &&
        typedStartEvent->represents<CompensateStartEvent>()
      ) {
        throw std::runtime_error("Model: compensation start event provided for process '" + typedStartEvent->parent->id + "'");
      }
    }

    // link outgoing sequence flows
    for ( auto& outflow : flowNode->element->outgoing ) {
      for (auto& sequenceFlow : flowNode->parent->sequenceFlows ) {
        if ( sequenceFlow->element->id.has_value() && outflow.get().textContent == sequenceFlow->id ) {
          flowNode->outgoing.push_back(sequenceFlow.get());

          // link optional default flow for gateways
          if ( auto id = flowNode->element->getOptionalAttributeByName("default");
               flowNode->represents<Gateway>() &&
               id.has_value() &&
               id.value().get().value.value == sequenceFlow->id
          ) {
            if ( auto exclusiveGateway = flowNode->represents<ExclusiveGateway>(); exclusiveGateway ) {
              exclusiveGateway->defaultFlow = sequenceFlow.get();
            }
            else if ( auto inclusiveGateway = flowNode->represents<InclusiveGateway>(); inclusiveGateway ) {
              inclusiveGateway->defaultFlow = sequenceFlow.get();
            }
            else if ( auto complexGateway = flowNode->represents<ComplexGateway>(); complexGateway ) {
              complexGateway->defaultFlow = sequenceFlow.get();
            }
          }
          break;
        }
      }
    }
  }
  // recurse
  if ( auto scope = flowNode->represents<Scope>(); scope ) {
    createNestedReferences(scope);
  }
}

void Model::createCompensations(Scope* scope) {
  std::unordered_map< std::string, Activity*> compensationActivityMap;
  std::unordered_map< std::string, CompensateBoundaryEvent*> compensateBoundaryEventMap;

  for ( auto compensationActivity : scope->compensationActivities ) {
    compensationActivityMap[compensationActivity->id] = compensationActivity;
  }

  for ( auto& childNode: scope->childNodes ) {
    if ( auto compensateBoundaryEvent = childNode->represents<CompensateBoundaryEvent>(); compensateBoundaryEvent ) {
      // add activity with compensate event attached to the boundary
      compensateBoundaryEventMap[compensateBoundaryEvent->id] = compensateBoundaryEvent;
    }
  }

  // determine compensation activity for each activity with a compensate event attached to the boundary
  for (XML::bpmn::tAssociation& association: scope->element->getChildren<XML::bpmn::tAssociation>() ) {
    auto it1 = compensateBoundaryEventMap.find(association.sourceRef.value);
    auto it2 = compensationActivityMap.find(association.targetRef.value);
    if ( it1 != compensateBoundaryEventMap.end() && it2 != compensationActivityMap.end() ) {
      it1->second->attachedTo->compensatedBy = it2->second;
    }
  }

  createCompensationReferences(scope);

  // recurse
  for ( auto& childNode: scope->childNodes ) {
    if ( auto childScope = childNode->represents<Scope>(); childScope ) {
      createCompensations(childScope);
    }
  }
}

void Model::createCompensationReferences(Scope* scope) {
  std::vector<CompensateThrowEvent*> compensateThrowEvents;
  std::vector<Activity*> compensatedActivities;

  for ( auto& childNode: scope->childNodes ) {
    if ( auto compensateThrowEvent = childNode->represents<CompensateThrowEvent>(); compensateThrowEvent ) {
      compensateThrowEvents.push_back(compensateThrowEvent);
    }
  }


  auto context = scope;
  if ( auto eventSubProcess = scope->represents<EventSubProcess>();
    eventSubProcess && 
    eventSubProcess->startEvent->represents<CompensateStartEvent>()
  ) {
    // compensation throw events in compensation event subprocess trigger 
    // compensation of activities in parent scope
    context = eventSubProcess->parent;
  }

  for ( auto& childNode: context->childNodes ) {
    if ( auto compensateBoundaryEvent = childNode->represents<CompensateBoundaryEvent>(); compensateBoundaryEvent ) {
      // add activity with compensate event attached to the boundary
      auto activity = compensateBoundaryEvent->attachedTo->as<Activity>();
      compensatedActivities.push_back(activity);
    }
    else if ( auto scope = childNode->represents<Scope>();
      // add subprocess with compensation event subprocess
      scope &&
      scope->compensationEventSubProcess
    ) {
      compensatedActivities.push_back(scope->as<SubProcess>());
    }
  }


  // determine activity to be compensated for compensate throw event
  for ( auto compensateThrowEvent : compensateThrowEvents ) {
    auto& eventDefinition = compensateThrowEvent->element->getChildren<XML::bpmn::tCompensateEventDefinition>()[0].get();

    std::string activityRef;

		// try to get activityRef from event definition
    if ( eventDefinition.activityRef.has_value() ) {
      activityRef = eventDefinition.activityRef.value().get().value.value;
    }

    if ( !activityRef.empty() ) {
      auto it = std::find_if(
        compensatedActivities.begin(),
        compensatedActivities.end(),
        [&activityRef](const Activity* activity) {
          return activity && activity->id == activityRef;
      });
      if ( it == compensatedActivities.end() ) {
        throw std::runtime_error("Model: Cannot find activity '" + activityRef + "' to be compensated");
      }
      compensateThrowEvent->activity = *it;
    }
    else if ( compensateThrowEvent->name.has_value() && !compensateThrowEvent->name.value().empty() ) {
      // use node name as fallback
      auto activityName = compensateThrowEvent->name.value();
      auto it = std::find_if(
        compensatedActivities.begin(),
        compensatedActivities.end(),
        [&activityName](const Activity* activity) {
          return activity && activity->name.has_value() && activity->name.value() == activityName;
      });
      if ( it == compensatedActivities.end() ) {
        throw std::runtime_error("Model: Cannot find activity with name '" + activityName + "' to be compensated");
      }
      compensateThrowEvent->activity = *it;
    }

  }

}

void Model::createLinks(Scope* scope) {
  std::vector<LinkSourceEvent*> linkSources;
  std::vector<LinkTargetEvent*> linkTargets;

  for ( auto& childNode: scope->childNodes ) {
    if ( auto linkSource = childNode->represents<LinkSourceEvent>(); linkSource ) {
      linkSources.push_back(linkSource);
    }
    if ( auto linkTarget = childNode->represents<LinkTargetEvent>(); linkTarget ) {
      linkTargets.push_back(linkTarget);
    }

    // recurse
    if ( auto childScope = childNode->represents<Scope>(); childScope ) {
      createLinks(childScope);
    }
  }

  for ( auto linkSource: linkSources ) {
    for ( auto linkTarget: linkTargets ) {
      if ( linkSource->name == linkTarget->name ) {
        if ( linkSource->target ) {
          throw std::runtime_error("Model: Link event '" + linkSource->id + "' has multiple targets");
        }
        linkSource->target = linkTarget;
        linkTarget->sources.push_back(linkSource);
      }
    }
    if ( !linkSource->target ) {
      throw std::runtime_error("Model: Link event '" + linkSource->id + "' has no target");
    }
  }

}

void Model::createMessageFlows() {
  // initialize map to resolve reference to participants
  std::unordered_map<std::string,std::string> participantMap;

  for ( auto& root : roots ) {
    if ( const auto& collaboration = root->getOptionalChild<XML::bpmn::tCollaboration>(); collaboration.has_value() ) {
 
      // add participants to map
      for ( const XML::bpmn::tParticipant& participant : collaboration->get().getChildren<XML::bpmn::tParticipant>() ) {
        if ( participant.processRef.has_value() ) {
          participantMap[participant.id->get().value] = participant.processRef->get().value;
        }
      }

      // create message flow objects
      for ( XML::bpmn::tMessageFlow& messageFlow : collaboration->get().getChildren<XML::bpmn::tMessageFlow>() ) {
        messageFlows.push_back(createMessageFlow(&messageFlow));
      }
    }
  }

  // create references
  for (auto& messageFlow : messageFlows ) {
    messageFlow->initialize(processes,participantMap);

    auto& [sourceProcess,sourceFlowNode] = messageFlow->source;
    if ( sourceFlowNode ) {
      sourceFlowNode->sending.push_back(messageFlow.get());
    }
    else if ( sourceProcess ) {
      sourceProcess->sending.push_back(messageFlow.get());
    }
    else {
      // nothing to do for message from empty collapsed participant
    }
    auto& [targetProcess,targetFlowNode] = messageFlow->target;
    if ( targetFlowNode ) {
      targetFlowNode->receiving.push_back(messageFlow.get());
    }
    else if ( targetProcess ) {
      targetProcess->receiving.push_back(messageFlow.get());
    }
    else {
      // nothing to do for message to empty collapsed participant
    }
  }

}


