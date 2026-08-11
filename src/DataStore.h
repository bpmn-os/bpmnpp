#ifndef BPMN_DataStore_H
#define BPMN_DataStore_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tDataStore.h"
#include "BaseElement.h"

namespace BPMN {

class DataStore : public BaseElement {
  friend class Model;
public:
  DataStore(XML::bpmn::tDataStore* dataStore);
  XML::bpmn::tDataStore* element;
protected:
};

} // namespace BPMN

#endif // BPMN_DataStore_H
