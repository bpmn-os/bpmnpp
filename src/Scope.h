#ifndef BPMN_Scope_H
#define BPMN_Scope_H

#include <memory>
#include <vector>
#include <optional>
#include "Node.h"

namespace BPMN {

class FlowNode;
class Activity;
class EventSubProcess;
class SequenceFlow;

/**
 * @brief Base class for BPMN elements that may contain a ChildNode elements.
 *
 * The `Scope` class provides functionalities to access child nodes,
 * event subprocesses, start nodes, and sequence flows associated 
 * with the scope.
 */
class Scope : virtual public Node {
  friend class Model;
public:
  Scope(XML::bpmn::tBaseElement* element);

  /// Vector containing all child nodes within the scope of the nodes.
  std::vector< std::unique_ptr<Node> > childNodes;

  /// Vector containing pointers to all flow nodes within the scope of the nodes.
  std::vector< FlowNode* > flowNodes;

  /// Vector containing pointers to all event subprocesses within the scope of the nodes.
  std::vector< EventSubProcess* > eventSubProcesses;

  /// Vector containing all flow nodes that may start execution of the scope.
  std::vector< FlowNode* > startEvents;

  /// Vector containing all sequence flows within the scope.
  std::vector< std::unique_ptr<SequenceFlow> > sequenceFlows;

  /// Vector containing pointers to all compensation activities within the scope.
  std::vector< Activity* > compensationActivities;

  /// Pointer to compensation  event subprocess of the scope.
  EventSubProcess* compensationEventSubProcess;

protected:
  void add(std::unique_ptr<Node> node);
  void add(std::unique_ptr<SequenceFlow> sequenceFlow);
};

} // namespace BPMN

#endif // BPMN_Scope_H
