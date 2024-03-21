#include "ExtensionElements.h"
#include "BaseElement.h"

using namespace BPMN;

ExtensionElements::ExtensionElements(XML::bpmn::tBaseElement* element)
  : element(getExtensionElements(element))
  , baseElement(nullptr)
{
}

ExtensionElements::~ExtensionElements() {}


XML::bpmn::tExtensionElements* ExtensionElements::getExtensionElements(XML::bpmn::tBaseElement* element) {
  if ( element->extensionElements.has_value() ) {
    return &element->extensionElements->get();
  }
  return nullptr;
}
