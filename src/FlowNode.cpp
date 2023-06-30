#include "FlowNode.h"
#include "xml/bpmn/tActivity.h"
#include "xml/bpmn/tSubProcess.h"

using namespace BPMN;

FlowNode::FlowNode(XML::bpmn::tFlowNode* flowNode, Scope* parent)
  : Node(flowNode)
  , element(flowNode)
  , parent(parent)
{
}

bool FlowNode::isStartNode() {
  return incoming.empty()
         && !( is<XML::bpmn::tActivity>() 
              && get<XML::bpmn::tActivity>()->isForCompensation.has_value() 
              && get<XML::bpmn::tActivity>()->isForCompensation->get() ) 
         && !( is<XML::bpmn::tSubProcess>() 
              && get<XML::bpmn::tSubProcess>()->triggeredByEvent.has_value() 
              && get<XML::bpmn::tSubProcess>()->triggeredByEvent->get() ) 
         ;
}

