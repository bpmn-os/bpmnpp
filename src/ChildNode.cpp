#include "ChildNode.h"
#include "xml/bpmn/tActivity.h"
#include "xml/bpmn/tSubProcess.h"

using namespace BPMN;

ChildNode::ChildNode(XML::bpmn::tBaseElement* element, Scope* parent)
  : Node(element)
  , parent(parent)
{
}
