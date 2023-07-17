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
    for ( auto flowNode: process->flowNodes ) {
      createReferences(flowNode);
    }
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

  return std::make_unique<FlowNode>(flowNode,parent);
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
    throw std::logic_error("Model: Activity is neither subProcess, callActivity, nor task");
  }

  return std::make_unique<Activity>(activity,parent);
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

  return std::make_unique<Event>(event,parent);
}

std::unique_ptr<FlowNode> Model::createBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent) {
  auto eventDefinitions = boundaryEvent->getChildren<XML::bpmn::tEventDefinition>();
  if ( eventDefinitions.empty() ) {
    throw std::runtime_error("Model: Boundary event has no event definition");
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
  
  throw std::logic_error("Model: Failed determining event definition for boundary event");

  return std::make_unique<BoundaryEvent>(boundaryEvent,parent);
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

  if ( eventDefinitions[0].get().is<XML::bpmn::tCompensateEventDefinition>() ) {
    return createCompensateStartEvent(catchEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tConditionalEventDefinition>() ) {
    return createConditionalCatchEvent(catchEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tErrorEventDefinition>() ) {
    return createErrorStartEvent(catchEvent,parent);
  }
  else if ( eventDefinitions[0].get().is<XML::bpmn::tEscalationEventDefinition>() ) {
    return createEscalationStartEvent(catchEvent,parent);
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

  throw std::logic_error("Model: Failed determining event definition for catching event");

  return createCatchEvent(catchEvent,parent);
}

std::unique_ptr<FlowNode> Model::createCompensateStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  return std::make_unique<CompensateStartEvent>(catchEvent,parent);
}

std::unique_ptr<FlowNode> Model::createConditionalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  return std::make_unique<ConditionalCatchEvent>(catchEvent,parent);
}

std::unique_ptr<FlowNode> Model::createErrorStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  return std::make_unique<ErrorStartEvent>(catchEvent,parent);
}

std::unique_ptr<FlowNode> Model::createEscalationStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent) {
  return std::make_unique<EscalationStartEvent>(catchEvent,parent);
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

  throw std::logic_error("Model: Failed determining event definition for throwing event");

  return createThrowEvent(throwEvent,parent);
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
    throw std::logic_error("Model: Gateway is neither parallel, exclusive, inclusive, complex, nor event-based gateway");
  }

  return std::make_unique<Gateway>(gateway,parent);
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

void Model::createChildNodes(Scope* scope) {
  // add child nodes (except boundary events and link events)
  for (XML::bpmn::tFlowNode& flowNode : scope->element->getChildren<XML::bpmn::tFlowNode>() ) {
    if ( flowNode.is<XML::bpmn::tEvent>() &&
         flowNode.getChildren<XML::bpmn::tLinkEventDefinition>().size()
    ) {
      throw std::runtime_error("Model: Link events are not yet supported");
    }

    if ( auto subProcess = flowNode.is<XML::bpmn::tSubProcess>();
         subProcess &&
         subProcess->triggeredByEvent.has_value() &&
         (bool)subProcess->triggeredByEvent->get()
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
    if ( auto scope = childNode->represents<Scope>(); scope ) {
      createSequenceFlows(scope);
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

void Model::createReferences(FlowNode* flowNode) {
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
    if ( flowNode->isStartNode() ) {
      flowNode->parent->startNodes.push_back(flowNode);
    }

    // link outgoing sequence flows
    for ( auto& outflow : flowNode->element->outgoing ) {
      for (auto& sequenceFlow : flowNode->parent->sequenceFlows ) {
        if ( sequenceFlow->get()->id.has_value() && outflow.get().textContent == (std::string)sequenceFlow->get()->id->get() ) {
          flowNode->outgoing.push_back(sequenceFlow.get());
          break;
        }
      }
    }
  }
  // recurse
  if ( auto scope = flowNode->represents<Scope>(); scope ) {
    for ( auto flowNode: scope->flowNodes ) {
      createReferences(flowNode);
    }
  }
}

