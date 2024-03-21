#ifndef BPMN_Node_H
#define BPMN_Node_H

#include "xml/bpmn/tBaseElement.h"
#include <memory>
#include <vector>
#include <optional>
#include <functional>
#include "BaseElement.h"
#include "ExtensionElements.h"

namespace BPMN {

class Model;
class Scope;

class MessageFlow;
/**
 * @brief Base class for all nodes in a BPMN model.
 *
 * The Node class encapsulates the information and relationships associated with a node in a BPMN process.
 * It can represent both a BPMN process itself or a flow node within a process. 
 */
class Node : public BaseElement {
  friend class Model;
public:
  /// @brief Constructs a Node object representing a BPMN process or flow node.
  Node(XML::bpmn::tBaseElement* element);

  /// @brief Vector containing all message flows going in to the node.
  std::vector< MessageFlow* > receiving;

  /// @brief Vector containing all message flows going out of the node.
  std::vector< MessageFlow* > sending;

  /**
   * @brief Returns the first node found matching a given condition.
   *
   * @return A pointer to a node matching condition, or `nullptr` if no such node exists
   */
  Node* find(std::function<bool(Node*)> condition);

  /**
   * @brief Returns the first node found matching a given condition.
   *
   * @return A pointer to a node matching condition, or `nullptr` if no such node exists
   */
  const Node* find(std::function<bool(const Node*)> condition) const;

  /**
   * @brief Returns all nodes matching a given condition.
   *
   * @return A vector of pointers to nodes matching condition
   */
  std::vector< Node* > find_all(std::function<bool(Node*)> condition);

  /**
   * @brief Returns all nodes matching a given condition.
   *
   * @return A vector of pointers to nodes matching condition
   */
  std::vector< const Node* > find_all(std::function<bool(const Node*)> condition) const;

};

} // namespace BPMN

#endif // BPMN_Node_H
