#ifndef BPMN_CatchEvent_H
#define BPMN_CatchEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "Event.h"

namespace BPMN {

class CatchEvent : public Event {
  friend class Model;
public:
  CatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  XML::bpmn::tCatchEvent* element;
};

} // namespace BPMN

#endif // BPMN_CatchEvent_H
