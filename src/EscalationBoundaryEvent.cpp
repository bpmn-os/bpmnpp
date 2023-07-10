#include "EscalationBoundaryEvent.h"

using namespace BPMN;

EscalationBoundaryEvent::EscalationBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : Node(boundaryEvent)
  , CatchEvent(boundaryEvent,parent)
  , BoundaryEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

