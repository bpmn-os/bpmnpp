#include "SequenceFlow.h"
#include "FlowNode.h"
#include "Scope.h"

using namespace BPMN;

SequenceFlow::SequenceFlow(XML::bpmn::tSequenceFlow* sequenceFlow, Scope* scope)
  : element(sequenceFlow)
  , source(findNode(sequenceFlow->sourceRef.value.value,scope))
  , target(findNode(sequenceFlow->targetRef.value.value,scope))
{
  id = sequenceFlow->id.has_value() ? (std::string)sequenceFlow->id->get().value : "";
}

FlowNode* SequenceFlow::findNode(std::string& nodeId, Scope* scope) {
  for ( auto& flowNode : scope->flowNodes ) {
    if ( flowNode->get<>()->id.has_value() && nodeId == flowNode->get<>()->id->get().value.value ) {
      return flowNode;
    }
  }

  throw std::runtime_error("SequenceFlow: cannot find node '" + nodeId + "' within scope '" + scope->id + "'" );
}

