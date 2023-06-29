#ifndef BPMN_TimerBoundaryEvent_H
#define BPMN_TimerBoundaryEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tBoundaryEvent.h"
#include "BoundaryEvent.h"

namespace BPMN {

class TimerBoundaryEvent : virtual public BoundaryEvent, virtual public CatchEvent {
  friend class Model;
public:
  TimerBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);

  XML::bpmn::tBoundaryEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_TimerBoundaryEvent_H
