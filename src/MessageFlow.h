#ifndef BPMN_MessageFlow_H
#define BPMN_MessageFlow_H

#include "xml/bpmn/tMessageFlow.h"
#include "ExtensionElements.h"

namespace BPMN {

class Model;
class Process;
class Scope;
class FlowNode;

/**
 * The `MessageFlow` class encapsulates the information and relationships associated with a message flow
 * in a BPMN process. The class provides access to the underlying `tMessageFlow` element and the source 
 * and target node.
 */
class MessageFlow {
public:
  /// Constructs a `MessageFlow` object based on a `tMessageFlow` element.
	MessageFlow(XML::bpmn::tMessageFlow* messageFlow);

  virtual ~MessageFlow() = default;

  XML::bpmn::tMessageFlow* element;

  /// Id of message flow
  std::string id;
  /// Reference to the source node of the message flow.
  std::pair<Process*, FlowNode*> source;
  /// Reference to the target node of the message flow.
  std::pair<Process*, FlowNode*> target;

  /**
   * Check if the message flow can be downcasted to a derived class T.
   * Returns true if the cast is successful, indicating that the element
   * is of type T. Otherwise, returns false.
   */
  template<typename T> bool represents() {
    return ( dynamic_cast<T*>(this) != nullptr );
  }
  /**
   * Attempt to downcast the message flow to a derived class T.
   * If the cast fails, throws a std::runtime_error with an error message
   * indicating an illegal cast operation.
   */
  template<typename T> T* as() {
    T* ptr = dynamic_cast<T*>(this); 
    if ( ptr == nullptr ) {
      throw std::runtime_error("MessageFlow: Illegal downcast");
    }
    return ptr; 
  }

  std::unique_ptr<ExtensionElements> extensionElements;
protected:
  friend class Model;
  void initialize(std::vector< std::unique_ptr<Process> >& processes, std::unordered_map<std::string,std::string>& participantMap);
  FlowNode* findRecursive(std::string& id, Scope* scope);
};

} // namespace BPMN

#endif // BPMN_MessageFlow_H

