#ifndef BPMN_BoundaryEvent_H
#define BPMN_BoundaryEvent_H

#include "xml/bpmn/tBoundaryEvent.h"
#include "Scope.h"
#include "CatchEvent.h"
#include "Activity.h"

namespace BPMN {

class Activity;

/**
 * @brief Base class for all boundary events attached to an Activity.
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
