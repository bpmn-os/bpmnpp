#include "SignalBoundaryEvent.h"

using namespace BPMN;

SignalBoundaryEvent::SignalBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : Node(boundaryEvent)
  , CatchEvent(boundaryEvent,parent)
  , BoundaryEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

