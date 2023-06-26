#ifndef BPMN_Node_H
#define BPMN_Node_H

#include "xml/bpmn/tProcess.h"
#include "xml/bpmn/tFlowNode.h"
#include "SequenceFlow.h"
#include <memory>
#include <vector>
#include <optional>

namespace BPMN {

class SequenceFlow;
class Model;

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
  /// Constructs a `Node` object representing a BPMN process.
	Node(XML::bpmn::tProcess& process);

  /// Constructs a `Node` object representing a BPMN flow node within a parent node.
  Node(XML::bpmn::tFlowNode& flowNode, Node* parentNode);

  virtual ~Node() = default;

  /// Reference to the parent node of flow nodes or nullopt for processes.
  Node* parentNode;

  /// Id of process or flow node.
  std::string id;

  /// Vector containing all flow nodes within the scope of the nodes.
  std::vector< std::unique_ptr<Node> > childNodes;

  /// Vector containing all flow nodes that may start execution of the current scope.
  std::vector< Node* > startNodes;

  /// Vector containing all sequence flows within the scope of the node.
  std::vector< std::unique_ptr<SequenceFlow> > sequenceFlows;

  /// Vector containing all incoming sequence flows of the node.
  std::vector< SequenceFlow* > incoming;

  /// Vector containing all outgoing sequence flows of the node.
  std::vector< SequenceFlow* > outgoing;

  /// Method that determines whether the node is a start node of its parent, i.e.,
  /// a flow node without incoming sequence flows which is not a  copmensation activity
  // and not an event-subprocess. 
  bool isStartNode();

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

protected:
  XML::bpmn::tBaseElement* element;
};

} // namespace BPMN

#endif // BPMN_Node_H
