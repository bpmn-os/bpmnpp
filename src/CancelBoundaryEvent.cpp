#include "CancelBoundaryEvent.h"

using namespace BPMN;

CancelBoundaryEvent::CancelBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : BoundaryEvent(boundaryEvent,parent)
  , Node(boundaryEvent,parent)
  , CatchEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

