#include "DataObject.h"
#include "ExtensionElements.h"

using namespace BPMN;

DataObject::DataObject(XML::bpmn::tDataObject* dataObject)
  : BaseElement(dataObject)
  , isCollection(dataObject->isCollection.has_value() && dataObject->isCollection.value().get().value)
  , element(dataObject)
{
}

