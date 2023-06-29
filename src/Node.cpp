#include "Node.h"
#include "FlowNode.h"

using namespace BPMN;

Node::Node(XML::bpmn::tBaseElement* element, Scope* parent) : element(element), parent(parent)
{
  id = element->id.has_value() ? (std::string)element->id->get() : "";
}
