#ifndef BPMN_SequenceFlow_H
#define BPMN_SequenceFlow_H

#include "xml/bpmn/tSequenceFlow.h"
#include "BaseElement.h"

namespace BPMN {

class Scope;
class FlowNode;

/**
 * @brief The SequenceFlow class encapsulates the information and relationships associated with a sequence flow
 * in a BPMN process.
 *
 * The class provides access to the underlying @ref XML::bpmn::tSequenceFlow element
 * and the source and target node.
 */
class SequenceFlow : public BaseElement {
public:
  //// @brief Constructs a SequenceFlow object based on a @ref XML::bpmn::tSequenceFlow element and the parent scope.
  SequenceFlow(XML::bpmn::tSequenceFlow* sequenceFlow, Scope* scope);

  XML::bpmn::tSequenceFlow* element;

  /// @brief Reference to the source node of the sequence flow.
  FlowNode* source;
  /// @brief Reference to the target node of the sequence flow.
  FlowNode* target;

protected:
  FlowNode* findNode(std::string& id, Scope* scope);
};

} // namespace BPMN

#endif // BPMN_SequenceFlow_H

