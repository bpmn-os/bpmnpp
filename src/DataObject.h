#ifndef BPMN_DataObject_H
#define BPMN_DataObject_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tDataObject.h"
#include "BaseElement.h"

namespace BPMN {

class DataObject : public BaseElement {
  friend class Model;
public:
  DataObject(XML::bpmn::tDataObject* dataObject);
  bool isCollection;
  XML::bpmn::tDataObject* element;
protected:
};

} // namespace BPMN

#endif // BPMN_DataObject_H
