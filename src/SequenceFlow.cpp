#include "SequenceFlow.h"
#include "FlowNode.h"
#include "Scope.h"

using namespace BPMN;

SequenceFlow::SequenceFlow(XML::bpmn::tSequenceFlow* sequenceFlow, Scope* scope) : sequenceFlow(sequenceFlow), source(getNode(sequenceFlow->sourceRef,scope)), target(getNode(sequenceFlow->targetRef,scope))
{
  id = sequenceFlow->id.has_value() ? (std::string)sequenceFlow->id->get() : "";
}

FlowNode* SequenceFlow::getNode(std::string id, Scope* scope) {
  for ( auto& flowNode : scope->childNodes ) {
    if ( flowNode->get()->id.has_value() && id == (std::string)flowNode->get()->id->get() ) {
      return flowNode.get();
    }
  }
  throw std::runtime_error("SequenceFlow: cannot find node");
}

