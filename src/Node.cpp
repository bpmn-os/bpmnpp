#include "Node.h"
#include "xml/bpmn/tActivity.h"
#include "xml/bpmn/tSubProcess.h"

using namespace BPMN;

Node::Node(XML::bpmn::tProcess& process) : element(&process), parentNode(nullptr)
{
  id = element->id.has_value() ? (std::string)element->id->get() : "";
}

Node::Node(XML::bpmn::tFlowNode& flowNode, Node* parentNode) : element(&flowNode), parentNode(parentNode)
{
  id = element->id.has_value() ? (std::string)element->id->get() : "";
}

bool Node::isStartNode() {
  return incoming.empty()
         && !( is<XML::bpmn::tActivity>() 
              && get<XML::bpmn::tActivity>()->isForCompensation.has_value() 
              && get<XML::bpmn::tActivity>()->isForCompensation->get() ) 
         && !( is<XML::bpmn::tSubProcess>() 
              && get<XML::bpmn::tSubProcess>()->triggeredByEvent.has_value() 
              && get<XML::bpmn::tSubProcess>()->triggeredByEvent->get() ) 
         ;
}
