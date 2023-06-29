#ifndef BPMN_ThrowEvent_H
#define BPMN_ThrowEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "Event.h"

namespace BPMN {

class ThrowEvent : public Event {
  friend class Model;
public:
  ThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);

  XML::bpmn::tThrowEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ThrowEvent_H
