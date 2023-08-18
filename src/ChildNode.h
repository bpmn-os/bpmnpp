#ifndef BPMN_ChildNode_H
#define BPMN_ChildNode_H

#include <memory>
#include <vector>
#include <optional>
#include "Node.h"

namespace BPMN {

class SequenceFlow;

/**
 * @brief Represents a node in a BPMN process that has a parent.
 */
class ChildNode : virtual public Node {
  friend class Model;
public:
  ChildNode(XML::bpmn::tBaseElement* element, Scope* parent);

  /// Reference to the parent node.
  Scope* parent;
};

} // namespace BPMN

#endif // BPMN_ChildNode_H
