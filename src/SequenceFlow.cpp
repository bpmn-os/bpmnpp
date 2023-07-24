#include "SequenceFlow.h"
#include "FlowNode.h"
#include "Scope.h"

using namespace BPMN;

SequenceFlow::SequenceFlow(XML::bpmn::tSequenceFlow* sequenceFlow, Scope* scope)
  : element(sequenceFlow)
  , source(findNode(sequenceFlow->sourceRef.value,scope))
  , target(findNode(sequenceFlow->targetRef.value,scope))
{
  id = sequenceFlow->id.has_value() ? (std::string)sequenceFlow->id->get() : "";
}

FlowNode* SequenceFlow::findNode(std::string& id, Scope* scope) {
  for ( auto& flowNode : scope->flowNodes ) {
    if ( flowNode->get<>()->id.has_value() && id == flowNode->get<>()->id->get().value ) {
      return flowNode;
    }
  }
  throw std::runtime_error("SequenceFlow: cannot find node");
}

