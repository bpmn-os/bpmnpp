#ifndef BPMN_Node_H
#define BPMN_Node_H

#include "xml/bpmn/tBaseElement.h"
#include <memory>
#include <vector>
#include <optional>
#include <functional>
#include "ExtensionElements.h"

namespace BPMN {

class Model;
class Scope;
class FlowNode;
/**
 * @brief Represents a node in a BPMN process.
 *
 * The `Node` class encapsulates the information and relationships associated with a node in a BPMN process.
 * It can represent both a BPMN process itself or a flow node within a process. The class allows to access
 * the underlying XML element.
 */
class Node {
  friend class Model;
public:
  /// Constructs a `Node` object representing a BPMN process or flow node.
  Node(XML::bpmn::tBaseElement* element);

  virtual ~Node() = default;


  /// Id of process or flow node.
  std::string id;

  /// Returns a pointer of type T of the element.
  template<typename T> T* is() {
    return dynamic_cast<T*>(element);
  }

  template<typename T> const T* is() const {
    return dynamic_cast<const T*>(element);
  }

  /**
   * Attempt to cast the element to the specified type T.
   * If the cast is successful, returns a pointer to the casted object.
   * If the cast fails, throws a std::runtime_error with an error message
   * indicating an illegal cast operation.
   */
  template<typename T = XML::bpmn::tBaseElement> T* get() {
    T* ptr = dynamic_cast<T*>(element); 
    if ( ptr == nullptr ) {
      throw std::runtime_error("Node: Illegal cast of element '" + (element->id.has_value() ? (std::string)element->id->get().value : "") + "'");
    }
    return ptr;
  }

  template<typename T = XML::bpmn::tBaseElement> const T* get() const {
    const T* ptr = dynamic_cast<const T*>(element);
    if ( ptr == nullptr ) {
      throw std::runtime_error("Node: Illegal cast of element '" + (element->id.has_value() ? (std::string)element->id->get().value : "") + "'");
    }
    return ptr;
  }

  /// Returns a pointer of type T of the node.
  template<typename T> T* represents() {
    return dynamic_cast<T*>(this);
  }

  /// Returns a pointer of type T of the node.
  template<typename T> const T* represents() const {
    return dynamic_cast<const T*>(this);
  }

  /**
   * Attempt to downcast the node to a derived class T.
   * If the cast fails, throws a std::runtime_error with an error message
   * indicating an illegal cast operation.
   */
  template<typename T> T* as() {
    T* ptr = dynamic_cast<T*>(this);
    if ( ptr == nullptr ) {
      throw std::runtime_error("Node: Illegal cast of node '" + this->id + "'");
    }
    return ptr;
  }

  /**
   * Attempt to downcast the node to a derived class T.
   * If the cast fails, throws a std::runtime_error with an error message
   * indicating an illegal cast operation.
   */
  template<typename T> const T* as() const {
    const T* ptr = dynamic_cast<const T*>(this);
    if ( ptr == nullptr ) {
      throw std::runtime_error("Node: Illegal cast of node '" + this->id + "'");
    }
    return ptr;
  }

  /**
   * Returns the first node found matching a given condition.
   *
   * @return A pointer to a node matching condition, or nullptr if no such node exists
   */
  Node* find(std::function<bool(Node*)> condition);

  /**
   * Returns the first node found matching a given condition.
   *
   * @return A pointer to a node matching condition, or nullptr if no such node exists
   */
  const Node* find(std::function<bool(const Node*)> condition) const;

  /**
   * Returns all nodes matching a given condition.
   *
   * @return A vector of pointers to nodes matching condition
   */
  std::vector< Node* > find_all(std::function<bool(Node*)> condition);

  /**
   * Returns all nodes matching a given condition.
   *
   * @return A vector of pointers to nodes matching condition
   */
  std::vector< const Node* > find_all(std::function<bool(const Node*)> condition) const;

  XML::bpmn::tBaseElement* element;

  std::unique_ptr<ExtensionElements> extensionElements;
};

} // namespace BPMN

#endif // BPMN_Node_H
