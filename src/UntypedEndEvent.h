#ifndef BPMN_UntypedEndEvent_H
#define BPMN_UntypedEndEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

class UntypedEndEvent : public ThrowEvent {
  friend class Model;
public:
  UntypedEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);

  XML::bpmn::tThrowEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_UntypedEndEvent_H
