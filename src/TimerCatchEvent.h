#ifndef BPMN_TimerCatchEvent_H
#define BPMN_TimerCatchEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "CatchEvent.h"

namespace BPMN {

class TimerCatchEvent : virtual public CatchEvent {
  friend class Model;
public:
  TimerCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);

  XML::bpmn::tCatchEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_TimerCatchEvent_H
