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

class MessageFlow;
/**
 * @brief Base class for all elements in a BPMN model.
 *
 * The Node class encapsulates the information and relationships associated with a node in a BPMN process.
 * It can represent both a BPMN process itself or a flow node within a process. The class allows to access
 * the underlying XML element.
 */
class Node {
  friend class Model;
public:
  /// @brief Constructs a Node object representing a BPMN process or flow node.
  Node(XML::bpmn::tBaseElement* element);

  virtual ~Node() = default;


  /// @brief Id of process or flow node.
  std::string id;

  /// @brief Vector containing all message flows going in to the node.
  std::vector< MessageFlow* > receiving;

  /// @brief Vector containing all message flows going out of the node.
  std::vector< MessageFlow* > sending;

  /** @brief Attempts to return the @ref element in the specified type T.
   * If the cast is successful, returns a pointer to the casted object.
   * If the cast fails, returns `nullptr`.
   */
  template<typename T> T* is() {
    return dynamic_cast<T*>(element);
  }

  /** @brief Attempts to return the @ref element in the specified type T.
   * If the cast is successful, returns a pointer to the casted object.
   * If the cast fails, returns `nullptr`.
   */
  template<typename T> const T* is() const {
    return dynamic_cast<const T*>(element);
  }

  /**
   * @brief Casts the @ref element to the specified type T.
   * If the cast is successful, returns a pointer to the casted object.
   * If the cast fails, throws a `std::runtime_error` with an error message
   * indicating an illegal cast operation.
   */
  template<typename T = XML::bpmn::tBaseElement> T* get() {
    T* ptr = dynamic_cast<T*>(element); 
    if ( ptr == nullptr ) {
      throw std::runtime_error("Node: Illegal cast of element '" + (element->id.has_value() ? (std::string)element->id->get().value : "") + "'");
    }
    return ptr;
  }

  /**
   * @brief Casts the element to the specified type T.
   * If the cast is successful, returns a pointer to the casted object.
   * If the cast fails, throws a `std::runtime_error` with an error message
   * indicating an illegal cast operation.
   */
  template<typename T = XML::bpmn::tBaseElement> const T* get() const {
    const T* ptr = dynamic_cast<const T*>(element);
    if ( ptr == nullptr ) {
      throw std::runtime_error("Node: Illegal cast of element '" + (element->id.has_value() ? (std::string)element->id->get().value : "") + "'");
    }
    return ptr;
  }

  /** @brief Attempts to cast the node to the specified type T.
   * If the cast is successful, returns a pointer to the casted node.
   * If the cast fails, returns `nullptr`.
   */
  template<typename T> T* represents() {
    return dynamic_cast<T*>(this);
  }

  /** @brief Attempts to cast the node to the specified type T.
   * If the cast is successful, returns a pointer to the casted node.
   * If the cast fails, returns `nullptr`.
   */
  template<typename T> const T* represents() const {
    return dynamic_cast<const T*>(this);
  }

  /**
   * @brief Casts the node to the specified type T.
   * If the cast fails, throws a `std::runtime_error` with an error message
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
   * @brief Casts the node to the specified type  T.
   * If the cast fails, throws a `std::runtime_error` with an error message
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

  XML::bpmn::tBaseElement* element;

  std::unique_ptr<ExtensionElements> extensionElements;
};

} // namespace BPMN

#endif // BPMN_Node_H
