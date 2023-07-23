#ifndef BPMN_Model_H
#define BPMN_Model_H

#include "Node.h"
#include "FlowNode.h"
#include "Process.h"
#include "EventSubProcess.h"
#include "SubProcess.h"
#include "CallActivity.h"
#include "AdHocSubProcess.h"
#include "Transaction.h"
#include "Task.h"
#include "UntypedTask.h"
#include "SendTask.h"
#include "ReceiveTask.h"
#include "UserTask.h"
#include "ManualTask.h"
#include "ScriptTask.h"
#include "BusinessRuleTask.h"
#include "ParallelGateway.h"
#include "ExclusiveGateway.h"
#include "InclusiveGateway.h"
#include "EventBasedGateway.h"
#include "ComplexGateway.h"
#include "ThrowEvent.h"
#include "CancelEndEvent.h"
#include "CompensateThrowEvent.h"
#include "ErrorEndEvent.h"
#include "EscalationThrowEvent.h"
#include "MessageThrowEvent.h"
#include "SignalThrowEvent.h"
#include "TerminateEvent.h"
#include "UntypedEndEvent.h"
#include "CatchEvent.h"
#include "CompensateStartEvent.h"
#include "ConditionalCatchEvent.h"
#include "ErrorStartEvent.h"
#include "EscalationStartEvent.h"
#include "MessageCatchEvent.h"
#include "SignalCatchEvent.h"
#include "TimerCatchEvent.h"
#include "UntypedStartEvent.h"
#include "BoundaryEvent.h"
#include "CancelBoundaryEvent.h"
#include "CompensateBoundaryEvent.h"
#include "ConditionalBoundaryEvent.h"
#include "ErrorBoundaryEvent.h"
#include "EscalationBoundaryEvent.h"
#include "MessageBoundaryEvent.h"
#include "SignalBoundaryEvent.h"
#include "TimerBoundaryEvent.h"
#include "SequenceFlow.h"
#include <memory>
#include <vector>
#include <string>


namespace BPMN {

class Node;
class SequenceFlow;


/**
 * @brief Represents a BPMN model with all its processes.
 *
 * The `Model` class encapsulates all processes with their nodes and sequence flows of a BPMN model.
 */
class Model {
protected:
	Model() {};
public:
	Model(const std::string& filename);
  virtual ~Model() = default;
  std::vector< std::unique_ptr<Process> > processes;
  std::vector<std::unique_ptr<XML::XMLObject> > roots;
protected:
  virtual void readBPMNFile(const std::string& filename);
  virtual std::unique_ptr<Process> createProcess(XML::bpmn::tProcess* process);
  virtual std::unique_ptr<EventSubProcess> createEventSubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent);

  virtual std::unique_ptr<FlowNode> createFlowNode(XML::bpmn::tFlowNode* flowNode, Scope* parent);

  virtual std::unique_ptr<FlowNode> createActivity(XML::bpmn::tActivity* activity, Scope* parent);

  virtual std::unique_ptr<FlowNode> createSubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent);
  virtual std::unique_ptr<FlowNode> createCallActivity(XML::bpmn::tCallActivity* callActivity, Scope* parent);
  virtual std::unique_ptr<FlowNode> createAdHocSubProcess(XML::bpmn::tAdHocSubProcess* adHocSubProcess, Scope* parent);
  virtual std::unique_ptr<FlowNode> createTransaction(XML::bpmn::tTransaction* transaction, Scope* parent);
  virtual std::unique_ptr<FlowNode> createTask(XML::bpmn::tTask* task, Scope* parent);

  virtual std::unique_ptr<FlowNode> createUntypedTask(XML::bpmn::tTask* task, Scope* parent);
  virtual std::unique_ptr<FlowNode> createSendTask(XML::bpmn::tSendTask* sendTask, Scope* parent);
  virtual std::unique_ptr<FlowNode> createReceiveTask(XML::bpmn::tReceiveTask* receiveTask, Scope* parent);
  virtual std::unique_ptr<FlowNode> createUserTask(XML::bpmn::tUserTask* userTask, Scope* parent);
  virtual std::unique_ptr<FlowNode> createManualTask(XML::bpmn::tManualTask* manualTask, Scope* parent);
  virtual std::unique_ptr<FlowNode> createScriptTask(XML::bpmn::tScriptTask* scriptTask, Scope* parent);
  virtual std::unique_ptr<FlowNode> createBusinessRuleTask(XML::bpmn::tBusinessRuleTask* businessRuleTask, Scope* parent);

  virtual std::unique_ptr<FlowNode> createEvent(XML::bpmn::tEvent* event, Scope* parent);

  virtual std::unique_ptr<FlowNode> createBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createCancelBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createCompensateBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createConditionalBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createErrorBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createEscalationBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createMessageBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createSignalBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createTimerBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);

  virtual std::unique_ptr<FlowNode> createCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createCompensateStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createConditionalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createErrorStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createEscalationStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createMessageCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createSignalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createTimerCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createUntypedStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);

  virtual std::unique_ptr<FlowNode> createThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createCancelEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createCompensateThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createErrorEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createEscalationThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createMessageThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createSignalThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createTerminateEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createUntypedEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createGateway(XML::bpmn::tGateway* gateway, Scope* parent);

  virtual std::unique_ptr<FlowNode> createParallelGateway(XML::bpmn::tParallelGateway* parallelGateway, Scope* parent);
  virtual std::unique_ptr<FlowNode> createExclusiveGateway(XML::bpmn::tExclusiveGateway* exclusiveGateway, Scope* parent);
  virtual std::unique_ptr<FlowNode> createInclusiveGateway(XML::bpmn::tInclusiveGateway* inclusiveGateway, Scope* parent);
  virtual std::unique_ptr<FlowNode> createEventBasedGateway(XML::bpmn::tEventBasedGateway* eventBasedGateway, Scope* parent);
  virtual std::unique_ptr<FlowNode> createComplexGateway(XML::bpmn::tComplexGateway* complexGateway, Scope* parent);

  virtual std::unique_ptr<SequenceFlow> createSequenceFlow(XML::bpmn::tSequenceFlow* sequenceFlow, Scope* scope);
  virtual void createChildNodes(Scope* scope);
  virtual void createSequenceFlows(Scope* scope);
  virtual void createReferences(FlowNode* flowNode);

  /// Binds the extension element to the given node
  template< typename T>
  static std::unique_ptr<T> bind(std::unique_ptr<T>&& node, std::unique_ptr<ExtensionElements>&& extensionElements) {
    node->extensionElements = std::move(extensionElements);
    return std::move(node);
  }

  /// Binds the extension element to the given node
  template< typename T>
  static std::unique_ptr<T> bind(std::unique_ptr<T>& node, std::unique_ptr<ExtensionElements>& extensionElements) {
    node->extensionElements = std::move(extensionElements);
    return std::move(node);
  }

  /// Binds the extension element to the given node
  template< typename T>
  static std::unique_ptr<T> bind(std::unique_ptr<T>& node, std::unique_ptr<ExtensionElements>&& extensionElements) {
    node->extensionElements = std::move(extensionElements);
    return std::move(node);
  }

  /// Binds the extension element to the given node
  template< typename T>
  static std::unique_ptr<T> bind(std::unique_ptr<T>&& node, std::unique_ptr<ExtensionElements>& extensionElements) {
    node->extensionElements = std::move(extensionElements);
    return std::move(node);
  }



};

} // namespace BPMN

#endif // BPMN_Model_H
