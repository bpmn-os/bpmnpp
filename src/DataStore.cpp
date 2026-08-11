#include "DataStore.h"
#include "ExtensionElements.h"

using namespace BPMN;

DataStore::DataStore(XML::bpmn::tDataStore* dataStore)
  : BaseElement(dataStore)
  , element(dataStore)
{
}

