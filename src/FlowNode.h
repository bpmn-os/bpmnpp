#ifndef BPMN_FlowNode_H
#define BPMN_FlowNode_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tFlowNode.h"
#include "ChildNode.h"

namespace BPMN {

class SequenceFlow;

/**
 * @brief Represents a flow node in a BPMN process.
 *
 * The `FlowNode` class encapsulates the information and relationships associated with a node in a BPMN process.
 * The class provides  allows to access the parent scope as well as incoming and outgoing sequence flows.
 */
class FlowNode : public ChildNode {
  friend class Model;
public:
  XML::bpmn::tFlowNode* element;
  FlowNode(XML::bpmn::tFlowNode* flowNode, Scope* parent);

  /// Method that determines whether the node is a start node of its parent, i.e.,
  /// a flow node without incoming sequence flows which is not a copmensation activity
  /// and not an event-subprocess. 
  bool isStartNode() const;

  /// Vector containing all incoming sequence flows of the node.
  std::vector< SequenceFlow* > incoming;

  /// Vector containing all outgoing sequence flows of the node.
  std::vector< SequenceFlow* > outgoing;

protected:
};

} // namespace BPMN

#endif // BPMN_FlowNode_H
