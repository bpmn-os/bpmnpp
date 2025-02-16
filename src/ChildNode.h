#ifndef BPMN_ChildNode_H
#define BPMN_ChildNode_H

#include <memory>
#include <vector>
#include <optional>
#include "Node.h"

namespace BPMN {

class SequenceFlow;

/**
 * @brief Base class for BPMN elements within a Scope.
 */
class ChildNode : virtual public Node {
  friend class Model;
public:
  ChildNode(XML::bpmn::tBaseElement* element, Scope* parent);
  
  /// @brief Returns the first ancestor node representing type T.
  template<typename T> Node* ancestor() {
    BPMN::Node* node = this;
    while ( node->represents<ChildNode>() ) {
      node = node->as<ChildNode>()->parent;
      if ( node->represents<T>() ) {
        return node;
      }
    }
    return nullptr;
  }

  /// @brief Returns the first ancestor node representing type T.
  template<typename T> const Node* ancestor() const {
    const BPMN::Node* node = this;
    while ( node->represents<ChildNode>() ) {
      node = node->as<ChildNode>()->parent;
      if ( node->represents<T>() ) {
        return node;
      }
    }
    return nullptr;
  }
  
  /// @brief Reference to the parent node.
  Scope* parent;
};

} // namespace BPMN

#endif // BPMN_ChildNode_H
