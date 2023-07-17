#include "SequenceFlow.h"
#include "FlowNode.h"
#include "Scope.h"

using namespace BPMN;

SequenceFlow::SequenceFlow(XML::bpmn::tSequenceFlow* sequenceFlow, Scope* scope) : sequenceFlow(sequenceFlow), source(findNode(sequenceFlow->sourceRef,scope)), target(findNode(sequenceFlow->targetRef,scope))
{
  id = sequenceFlow->id.has_value() ? (std::string)sequenceFlow->id->get() : "";
}

FlowNode* SequenceFlow::findNode(std::string id, Scope* scope) {
  for ( auto& flowNode : scope->flowNodes ) {
    if ( flowNode->get<>()->id.has_value() && id == (std::string)flowNode->get<>()->id->get() ) {
      return flowNode;
    }
  }
  throw std::runtime_error("SequenceFlow: cannot find node");
}

