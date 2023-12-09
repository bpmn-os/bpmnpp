#ifndef BPMN_BoundaryEvent_H
#define BPMN_BoundaryEvent_H

#include "xml/bpmn/tBoundaryEvent.h"
#include "Scope.h"
#include "CatchEvent.h"
#include "Activity.h"

namespace BPMN {

class Activity;

/**
 * @brief Represents a boundary event attached to an activity in a BPMN process.
 */
class BoundaryEvent : virtual public CatchEvent {
  friend class Model;
public:
  BoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  bool isInterrupting;
  Activity* attachedTo;
protected:
  Activity* resolveReference();
};

} // namespace BPMN

#endif // BPMN_BoundaryEvent_H
