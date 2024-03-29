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
#include "LinkSourceEvent.h"
#include "UntypedEndEvent.h"
#include "CatchEvent.h"
#include "ConditionalCatchEvent.h"
#include "MessageCatchEvent.h"
#include "SignalCatchEvent.h"
#include "TimerCatchEvent.h"
#include "LinkTargetEvent.h"
#include "UntypedStartEvent.h"
#include "TypedStartEvent.h"
#include "CompensateStartEvent.h"
#include "ErrorStartEvent.h"
#include "EscalationStartEvent.h"
#include "ConditionalStartEvent.h"
#include "MessageStartEvent.h"
#include "SignalStartEvent.h"
#include "TimerStartEvent.h"
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
#include "MessageFlow.h"
#include "DataObject.h"
#include <memory>
#include <vector>
#include <string>

/**
 * @brief The `BPMN` namespace contains linked classes representing a BPMN model.
 *
 * For each supported BPMN element a wrapper is used that contains an `element`
 * attribute which is a pointer to the raw representation of the respective element
 * in the BPMN file according to the XML-schema.
 * @see XML::bpmn
 */
namespace BPMN {

class Node;
class SequenceFlow;
class MessageFlow;


/**
 * @brief Represents a BPMN model with all its processes and message flows.
 *
 * The Model class reads a BPMN model from a file and provides access to all processes
 * with their content as well as to all message flows in a BPMN model.
 * @see @ref Process, @ref MessageFlow
 * @note The BPMN model is expected to conform with the BPMN specification, e.g.,
 * it is expected that all boundary events and start events of event subprocesses have
 * an event definition.
 * @par
 * @note All nodes in a process model are derived from an abstract class @ref Node. The
 * class model uses multiple inheritance to provide type specific attributes. References
 * are usually provided by pointers to a base class. Casting is required to gain access
 * to type specific attributes.
 * @par
 * @note The BPMN extension mechanism can be used by providing a custom model class derived
 * from @ref Model and a custom extension derived from the abstract base class
 * @ref ExtensionElements. The following example shows how an object of the custom extension
 * `MyExtensionElements` class can be bound to processes by overriding the method
 * @ref Model::createProcess in the custom model `MyModel` class:
 * ```
 * std::unique_ptr<BPMN::Process> MyModel::createProcess(XML::bpmn::tProcess* process) {
 *   return bind<BPMN::Process>(
 *     BPMN::Model::createProcess(process),
 *     std::make_unique<MyExtensionElements>(process)
 *   );
 * }
 * ```
 *
 * @warning Multiple event definitions are not yet supported. A `std::runtime_error`
 * will be thrown when parsing an event with multiple event definitions.
 *
 * References between different classes are automatically determined:
 * - For each sequence flow and each message flow, pointers to the source and target
 *   are provided.
 *   @see @ref SequenceFlow, @ref MessageFlow, @ref FlowNode, @ref Process
 *
 * - For each node, pointers to receiving and sending message flows are provided.
 *   @see Node
 * - For each BPMN element that may have child nodes within its scope, the child nodes
 *   and sequence flows between them are owned by the node. Pointers to each flow node,
 *   event subprocess,  start events, compensation activities, and compensation event
 *   subprocess are given.
 *   @see @ref Scope
 * - For each node within a scope, a pointer to the parent scope is provided.
 *   @see @ref ChildNode
 * - For each node that may receive a flow token, pointers to all incoming and outgoing
 *   sequence flows are given.
 *   @see @ref FlowNode, @ref SequenceFlow
 * - For each subprocess, a pointer to the start event is provided.
 *   @attention It is expected that each subprocess has a unique @ref UntypedStartEvent.
 *   @see @ref SubProcess
 * - For each event subprocess, a pointer to the start event is provided.
 *   @attention It is expected that each event subprocess has a unique @ref TypedStartEvent.
 *   @see @ref EventSubProcess
 * - For each activity, pointers to each boundary event (excluding the compensation
 *   boundary event) are provided.
 *   @see @ref Activity, @ref BoundaryEvent
 * - For each activity that can be compensated, a pointer to the compensation activity
 *   or compensation event subprocess is provided.
 *   @attention Activities must not have both compensation activity and compensation event
 *              subprocess.
 *   @see @ref Activity, @ref CompensateBoundaryEvent, @ref CompensateStartEvent
 * - For each event attached to the boundary of an activity, a pointer to the activity
 *   is provided.
 *   @see @ref Activity, @ref BoundaryEvent
 * - For each link event, a pointer to the respective target or source(s) is provided.
 *   @note Target and sources are matched based on the
 *         @ref XML::bpmn::tLinkEventDefinition::name attribute in the link event
 *         definition. If no such name is given, the @ref FlowNode::name attribute of the link
 *         event is used as fallback.
 *   @attention For each link source exactly one link target must be found, otherwise a
 *              `std::runtime_error` will be thrown.
 *   @see @ref LinkSourceEvent, @ref LinkTargetEvent, @ref XML::bpmn::tLinkEventDefinition,
 *        @ref  FlowNode
 * - For each throwing compensation event, a pointer to the activity to be compensated is
 *   provided.
 *   @note The respective activity is determined based on the
 *         @ref XML::bpmn::tCompensateEventDefinition::activityRef attribute of the
 *         compensation event definition and the @ref Node::id attribute of the activity. If
 *         no such attribute reference is given, respective activity is determined based on the 
 *         @ref FlowNode::name attribute of the compensate throw event and the @ref FlowNode::name
 *         of the activity.
 *   @attention Compensation throw events in compensation event subprocesses can only trigger
 *              compensation of activities within parent scope. All other compensation throw events can
 *              only trigger compensation of activities within the same scope.
 *   @see @ref CompensateThrowEvent, @ref XML::bpmn::tCompensateEventDefinition, @ref Activity,
 *        @ref  FlowNode
 **/
class Model {
protected:
	Model() {};
public:
	Model(const std::string& filename);
  virtual ~Model() = default;
  std::vector<std::unique_ptr<XML::XMLObject> > roots;
  std::vector< std::unique_ptr<Process> > processes;
  std::vector< std::unique_ptr<MessageFlow> > messageFlows;
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

  virtual std::unique_ptr<FlowNode> createConditionalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createMessageCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createSignalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createTimerCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createLinkTargetEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);

  virtual std::unique_ptr<FlowNode> createTypedStartEvent(XML::bpmn::tStartEvent* startEvent, XML::bpmn::tEventDefinition& eventDefinition, Scope* parent);

  virtual std::unique_ptr<FlowNode> createCompensateStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createErrorStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createEscalationStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createConditionalStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createMessageStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createSignalStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createTimerStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);

  virtual std::unique_ptr<FlowNode> createUntypedStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);

  virtual std::unique_ptr<FlowNode> createThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createCancelEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createCompensateThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createErrorEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createEscalationThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createMessageThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createSignalThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createTerminateEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createLinkSourceEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createUntypedEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  virtual std::unique_ptr<FlowNode> createGateway(XML::bpmn::tGateway* gateway, Scope* parent);

  virtual std::unique_ptr<FlowNode> createParallelGateway(XML::bpmn::tParallelGateway* parallelGateway, Scope* parent);
  virtual std::unique_ptr<FlowNode> createExclusiveGateway(XML::bpmn::tExclusiveGateway* exclusiveGateway, Scope* parent);
  virtual std::unique_ptr<FlowNode> createInclusiveGateway(XML::bpmn::tInclusiveGateway* inclusiveGateway, Scope* parent);
  virtual std::unique_ptr<FlowNode> createEventBasedGateway(XML::bpmn::tEventBasedGateway* eventBasedGateway, Scope* parent);
  virtual std::unique_ptr<FlowNode> createComplexGateway(XML::bpmn::tComplexGateway* complexGateway, Scope* parent);

  virtual std::unique_ptr<SequenceFlow> createSequenceFlow(XML::bpmn::tSequenceFlow* sequenceFlow, Scope* scope);
  virtual std::unique_ptr<DataObject> createDataObject(XML::bpmn::tDataObject* dataObject, BPMN::Scope* scope);
  virtual std::unique_ptr<MessageFlow> createMessageFlow(XML::bpmn::tMessageFlow* messageFlow);
  virtual void createChildNodes(Scope* scope);
  virtual void createSequenceFlows(Scope* scope);
  virtual void createNestedReferences(Scope* scope);
  virtual void createFlowReferences(FlowNode* flowNode);
  virtual void createCompensations(Scope* scope);
  virtual void createCompensationReferences(Scope* scope);
  virtual void createLinks(Scope* scope);
  virtual void createMessageFlows();

  /// Binds the extension elements to the given baseElement
  template< typename T>
  static std::unique_ptr<T> bind(std::unique_ptr<T>&& baseElement, std::unique_ptr<ExtensionElements>&& extensionElements) {
    baseElement->extensionElements = std::move(extensionElements);
    baseElement->extensionElements->baseElement = baseElement.get();
    return std::move(baseElement);
  }

  /// Binds the extension elements to the given baseElement
  template< typename T>
  static std::unique_ptr<T> bind(std::unique_ptr<T>& baseElement, std::unique_ptr<ExtensionElements>& extensionElements) {
    baseElement->extensionElements = std::move(extensionElements);
    baseElement->extensionElements->baseElement = baseElement.get();
    return std::move(baseElement);
  }

  /// Binds the extension elements to the given baseElement
  template< typename T>
  static std::unique_ptr<T> bind(std::unique_ptr<T>& baseElement, std::unique_ptr<ExtensionElements>&& extensionElements) {
    baseElement->extensionElements = std::move(extensionElements);
    baseElement->extensionElements->baseElement = baseElement.get();
    return std::move(baseElement);
  }

  /// Binds the extension elements to the given baseElement
  template< typename T>
  static std::unique_ptr<T> bind(std::unique_ptr<T>&& baseElement, std::unique_ptr<ExtensionElements>& extensionElements) {
    baseElement->extensionElements = std::move(extensionElements);
    baseElement->extensionElements->baseElement = baseElement.get();
    return std::move(baseElement);
  }



};

} // namespace BPMN

#endif // BPMN_Model_H
