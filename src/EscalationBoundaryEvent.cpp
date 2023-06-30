#include "EscalationBoundaryEvent.h"

using namespace BPMN;

EscalationBoundaryEvent::EscalationBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : BoundaryEvent(boundaryEvent,parent)
  , Node(boundaryEvent)
  , CatchEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

