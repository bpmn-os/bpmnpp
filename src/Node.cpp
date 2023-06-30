#include "Node.h"
#include "FlowNode.h"

using namespace BPMN;

Node::Node(XML::bpmn::tBaseElement* element) : element(element)
{
  id = element->id.has_value() ? (std::string)element->id->get() : "";

  if ( element->extensionElements.has_value() ) {
    extensionElements = std::make_unique<ExtensionElements>( &element->extensionElements->get() );
  }
}
