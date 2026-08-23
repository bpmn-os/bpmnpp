# The generated classes live in XML_DIR, which is in the build tree, while the hand-written sources live in
# SOURCE_DIR, so the two sets no longer share a prefix and are kept apart until both have been resolved.
# The generated CMakeLists writes the unqualified names, so they are moved aside first.
include("${XML_DIR}/bpmn/CMakeLists.txt")

set(bpmn_xml_SOURCES ${bpmn_SOURCES})
set(bpmn_xml_HEADERS ${bpmn_HEADERS})

list(TRANSFORM bpmn_xml_SOURCES PREPEND "${XML_DIR}/")
list(TRANSFORM bpmn_xml_HEADERS PREPEND "${XML_DIR}/")

list(PREPEND bpmn_xml_SOURCES ${XML_DIR}/XMLObject.cpp)
list(PREPEND bpmn_xml_HEADERS ${XML_DIR}/XMLObject.h)

set(bpmn_SOURCES
  Element.cpp
  BaseElement.cpp
  ExtensionElements.cpp
  DataStore.cpp
  DataObject.cpp
  Node.cpp
  Scope.cpp
  ChildNode.cpp
  Process.cpp
  EventSubProcess.cpp
  SequenceFlow.cpp
  FlowNode.cpp
  Event.cpp
  CatchEvent.cpp
  ConditionalCatchEvent.cpp
  MessageCatchEvent.cpp
  SignalCatchEvent.cpp
  TimerCatchEvent.cpp
  LinkTargetEvent.cpp
  UntypedStartEvent.cpp
  TypedStartEvent.cpp
  CompensateStartEvent.cpp
  ErrorStartEvent.cpp
  EscalationStartEvent.cpp
  ConditionalStartEvent.cpp
  MessageStartEvent.cpp
  SignalStartEvent.cpp
  TimerStartEvent.cpp
  ThrowEvent.cpp
  UntypedEndEvent.cpp
  CancelEndEvent.cpp
  CompensateThrowEvent.cpp
  ErrorEndEvent.cpp
  EscalationThrowEvent.cpp
  MessageThrowEvent.cpp
  SignalThrowEvent.cpp
  TerminateEvent.cpp
  LinkSourceEvent.cpp
  BoundaryEvent.cpp
  CancelBoundaryEvent.cpp
  CompensateBoundaryEvent.cpp
  ConditionalBoundaryEvent.cpp
  ErrorBoundaryEvent.cpp
  EscalationBoundaryEvent.cpp
  MessageBoundaryEvent.cpp
  SignalBoundaryEvent.cpp
  TimerBoundaryEvent.cpp
  Activity.cpp
  SubProcess.cpp
  Task.cpp
  AbstractTask.cpp
  BusinessRuleTask.cpp
  ManualTask.cpp
  ReceiveTask.cpp
  ScriptTask.cpp
  SendTask.cpp
  UserTask.cpp
  CallActivity.cpp
  AdHocSubProcess.cpp
  Transaction.cpp
  Gateway.cpp
  ParallelGateway.cpp
  ExclusiveGateway.cpp
  InclusiveGateway.cpp
  ComplexGateway.cpp
  EventBasedGateway.cpp
  MessageFlow.cpp
  Model.cpp
)

list(TRANSFORM bpmn_SOURCES PREPEND "${SOURCE_DIR}/")
list(PREPEND bpmn_SOURCES ${bpmn_xml_SOURCES})

set(bpmn_HEADERS
  Element.h
  BaseElement.h
  ExtensionElements.h
  DataStore.h
  DataObject.h
  Node.h
  Scope.h
  ChildNode.h
  Process.h
  EventSubProcess.h
  SequenceFlow.h
  FlowNode.h
  Event.h
  CatchEvent.h
  ConditionalCatchEvent.h
  MessageCatchEvent.h
  SignalCatchEvent.h
  TimerCatchEvent.h
  LinkTargetEvent.h
  UntypedStartEvent.h
  TypedStartEvent.h
  CompensateStartEvent.h
  ErrorStartEvent.h
  EscalationStartEvent.h
  ConditionalStartEvent.h
  MessageStartEvent.h
  SignalStartEvent.h
  TimerStartEvent.h
  ThrowEvent.h
  UntypedEndEvent.h
  CancelEndEvent.h
  CompensateThrowEvent.h
  ErrorEndEvent.h
  EscalationThrowEvent.h
  MessageThrowEvent.h
  SignalThrowEvent.h
  TerminateEvent.h
  LinkSourceEvent.h
  BoundaryEvent.h
  CancelBoundaryEvent.h
  CompensateBoundaryEvent.h
  ConditionalBoundaryEvent.h
  ErrorBoundaryEvent.h
  EscalationBoundaryEvent.h
  MessageBoundaryEvent.h
  SignalBoundaryEvent.h
  TimerBoundaryEvent.h
  Activity.h
  SubProcess.h
  Task.h
  AbstractTask.h
  BusinessRuleTask.h
  ManualTask.h
  ReceiveTask.h
  ScriptTask.h
  SendTask.h
  UserTask.h
  CallActivity.h
  AdHocSubProcess.h
  Transaction.h
  Gateway.h
  ParallelGateway.h
  ExclusiveGateway.h
  InclusiveGateway.h
  ComplexGateway.h
  EventBasedGateway.h
  MessageFlow.h
  Model.h
)

# The xml set goes first, as it did when both were relative: the amalgamated header is these files
# concatenated in list order, so XMLObject and the generated classes must precede what derives from them.
list(TRANSFORM bpmn_HEADERS PREPEND "${SOURCE_DIR}/")
list(PREPEND bpmn_HEADERS ${bpmn_xml_HEADERS})
