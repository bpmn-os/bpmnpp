#include "CompensateBoundaryEvent.h"

using namespace BPMN;

CompensateBoundaryEvent::CompensateBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : Node(boundaryEvent)
  , CatchEvent(boundaryEvent,parent)
  , BoundaryEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

