#ifndef BPMN_MessageFlow_H
#define BPMN_MessageFlow_H

#include "xml/bpmn/tMessageFlow.h"
#include "BaseElement.h"

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
class MessageFlow : public BaseElement {
public:
  /// @brief Constructs a MessageFlow object based on a @ref XML::bpmn::tMessageFlow element.
  MessageFlow(XML::bpmn::tMessageFlow* messageFlow);

  XML::bpmn::tMessageFlow* element;

  /// @brief Reference to the source node of the message flow.
  std::pair<Process*, FlowNode*> source;
  /// @brief Reference to the target node of the message flow.
  std::pair<Process*, FlowNode*> target;
protected:
  friend class Model;
  void initialize(std::vector< std::unique_ptr<Process> >& processes, std::unordered_map<std::string,std::string>& participantMap);
  FlowNode* findRecursive(std::string& id, Scope* scope);
};

} // namespace BPMN

#endif // BPMN_MessageFlow_H

