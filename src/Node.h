#ifndef BPMN_Node_H
#define BPMN_Node_H

#include "xml/bpmn/tBaseElement.h"
#include <memory>
#include <vector>
#include <optional>
#include "ExtensionElements.h"

namespace BPMN {

class Model;
class Scope;
class FlowNode;

/**
 * @brief Represents a node in a BPMN process.
 *
 * The `Node` class encapsulates the information and relationships associated with a node in a BPMN process.
 * It can represent both a BPMN process itself or a flow node within a process. The class provides
 * functionalities to access the underlying XML element, the parent node, child nodes, start
 * nodes, and sequence flows associated with the current node.
 */
class Node {
  friend class Model;
public:
  /// Constructs a `Node` object representing a BPMN process or flow node within a parent node.
  Node(XML::bpmn::tBaseElement* element, Scope* parent = nullptr);

  virtual ~Node() = default;

  /// Reference to the parent node of flow nodes or nullopt for processes.
  Scope* parent;

  /// Id of process or flow node.
  std::string id;

  /// Returns a pointer of type T of the element.
  template<typename T> T* is() {
    return dynamic_cast<T*>(element);
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
      throw std::runtime_error("Node: Illegal element cast");
    }
    return ptr; 
  };

  /// Returns a pointer of type T of the node.
  template<typename T> T* represents() {
    return dynamic_cast<T*>(this);
  }

  /**
   * Attempt to downcast the node to a derived class T.
   * If the cast fails, throws a std::runtime_error with an error message
   * indicating an illegal cast operation.
   */
  template<typename T> T* as() {
    T* ptr = dynamic_cast<T*>(this); 
    if ( ptr == nullptr ) {
      throw std::runtime_error("Node: Illegal downcast");
    }
    return ptr; 
  };

  std::unique_ptr<ExtensionElements> extensionElements;

  XML::bpmn::tBaseElement* element;
};

} // namespace BPMN

#endif // BPMN_Node_H
