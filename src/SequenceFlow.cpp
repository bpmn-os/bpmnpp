#include "SequenceFlow.h"

using namespace BPMN;

SequenceFlow::SequenceFlow(XML::bpmn::tSequenceFlow& sequenceFlow, Node* scope) : sequenceFlow(&sequenceFlow), source(getNode(sequenceFlow.sourceRef,scope)), target(getNode(sequenceFlow.targetRef,scope))
{
  id = sequenceFlow.id.has_value() ? (std::string)sequenceFlow.id->get() : "";
}

Node* SequenceFlow::getNode(std::string id, Node* scope) {
  for ( auto& node : scope->childNodes ) {
    if ( node->get()->id.has_value() && id == (std::string)node->get()->id->get() ) {
      return node.get();
    }
  }
  throw std::runtime_error("SequenceFlow: cannot find node");
}

