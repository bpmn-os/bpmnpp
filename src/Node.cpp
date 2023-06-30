#include "Node.h"
#include "FlowNode.h"

using namespace BPMN;

Node::Node(XML::bpmn::tBaseElement* element)
  : element(element)
  , extensionElements(std::make_unique<ExtensionElements>(element))
{
  id = element->id.has_value() ? (std::string)element->id->get() : "";
}
