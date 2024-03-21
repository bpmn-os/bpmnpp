#include "BaseElement.h"
#include "ExtensionElements.h"

using namespace BPMN;

BaseElement::BaseElement(XML::bpmn::tBaseElement* element)
  : element(element)
  , extensionElements(std::make_unique<ExtensionElements>(element))
{
  id = element->id.has_value() ? (std::string)element->id->get().value : "";
}
