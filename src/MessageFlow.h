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
 * @brief The MessageFlow class encapsulates the information and relationships associated with
 * a message flow in a BPMN process.
 *
 * The class provides access to the underlying @ref XML::bpmn::tMessageFlow element and the source
 * and target node.
 */
class MessageFlow {
public:
  /// @brief Constructs a MessageFlow object based on a @ref XML::bpmn::tMessageFlow element.
	MessageFlow(XML::bpmn::tMessageFlow* messageFlow);

  virtual ~MessageFlow() = default;

  XML::bpmn::tMessageFlow* element;

  /// @brief Id of message flow
  std::string id;
  /// @brief Reference to the source node of the message flow.
  std::pair<Process*, FlowNode*> source;
  /// @brief Reference to the target node of the message flow.
  std::pair<Process*, FlowNode*> target;

  /// @brief BPMN extension elements provided for the message flow.
  std::unique_ptr<ExtensionElements> extensionElements;
protected:
  friend class Model;
  void initialize(std::vector< std::unique_ptr<Process> >& processes, std::unordered_map<std::string,std::string>& participantMap);
  FlowNode* findRecursive(std::string& id, Scope* scope);
};

} // namespace BPMN

#endif // BPMN_MessageFlow_H

