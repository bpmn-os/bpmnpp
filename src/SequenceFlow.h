#ifndef BPMN_SequenceFlow_H
#define BPMN_SequenceFlow_H

#include "xml/bpmn/tSequenceFlow.h"
#include "ExtensionElements.h"

namespace BPMN {

class Scope;
class FlowNode;

/**
 * @brief Represents a sequence flow in a BPMN process.
 *
 * The `SequenceFlow` class encapsulates the information and relationships associated with a sequence flow
 * in a BPMN process. The class provides access to the underlying `tSequenceFlow` element and the source 
 * and target node.
 */
class SequenceFlow {
public:
  //// Constructs a `SequenceFlow` object based on a `tSequenceFlow` element and the parent scope.
	SequenceFlow(XML::bpmn::tSequenceFlow* sequenceFlow, Scope* scope);

  virtual ~SequenceFlow() = default;

  //// Overloaded arrow operator to provide access to the underlying `tSequenceFlow` element.
  XML::bpmn::tSequenceFlow* get() { return sequenceFlow; };

  XML::bpmn::tSequenceFlow* sequenceFlow;

  /// Id of sequence flow
  std::string id;
  /// Reference to the source node of the sequence flow.
  FlowNode* source;
  /// Reference to the target node of the sequence flow.
  FlowNode* target;

  /**
   * Check if the sequence flow can be downcasted to a derived class T.
   * Returns true if the cast is successful, indicating that the element
   * is of type T. Otherwise, returns false.
   */
  template<typename T> bool represents() {
    return ( dynamic_cast<T*>(this) != nullptr );
  }
  /**
   * Attempt to downcast the sequence flow to a derived class T.
   * If the cast fails, throws a std::runtime_error with an error message
   * indicating an illegal cast operation.
   */
  template<typename T> T* as() {
    T* ptr = dynamic_cast<T*>(this); 
    if ( ptr == nullptr ) {
      throw std::runtime_error("SequenceFlow: Illegal downcast");
    }
    return ptr; 
  }


  std::unique_ptr<ExtensionElements> extensionElements;
protected:
  FlowNode* findNode(std::string id, Scope* scope);
};

} // namespace BPMN

#endif // BPMN_SequenceFlow_H

