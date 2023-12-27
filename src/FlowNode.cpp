#include "FlowNode.h"
#include "xml/bpmn/tActivity.h"
#include "xml/bpmn/tSubProcess.h"

using namespace BPMN;

FlowNode::FlowNode(XML::bpmn::tFlowNode* flowNode, Scope* parent)
  : Node(flowNode)
  , ChildNode(flowNode,parent)
  , element(flowNode)
{
  if ( flowNode->name.has_value() ) {
    name = flowNode->name.value().get().value;
  }
}
