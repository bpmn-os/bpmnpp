#include "CompensateBoundaryEvent.h"

using namespace BPMN;

CompensateBoundaryEvent::CompensateBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : BoundaryEvent(boundaryEvent,parent)
  , Node(boundaryEvent)
  , CatchEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

