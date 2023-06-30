#include "ExtensionElements.h"

using namespace BPMN;

ExtensionElements::ExtensionElements(XML::bpmn::tBaseElement* baseElement)
  : element(getExtensionElements(baseElement))
{
}

ExtensionElements::~ExtensionElements() {}


XML::bpmn::tExtensionElements* ExtensionElements::getExtensionElements(XML::bpmn::tBaseElement* baseElement) {
  if ( baseElement->extensionElements.has_value() ) {
    return &baseElement->extensionElements->get();
  }
  return nullptr;
}
