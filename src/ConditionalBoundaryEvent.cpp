#include "ConditionalBoundaryEvent.h"

using namespace BPMN;

ConditionalBoundaryEvent::ConditionalBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : BoundaryEvent(boundaryEvent,parent)
  , Node(boundaryEvent,parent)
  , CatchEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

