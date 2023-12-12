#ifndef BPMN_TimerStartEvent_H
#define BPMN_TimerStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tStartEvent.h"
#include "TimerCatchEvent.h"
#include "TypedStartEvent.h"

namespace BPMN {

class TimerStartEvent : public TimerCatchEvent, public TypedStartEvent {
  friend class Model;
public:
  TimerStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);

  XML::bpmn::tStartEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_TimerStartEvent_H
