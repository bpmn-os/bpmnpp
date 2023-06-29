#include "SignalBoundaryEvent.h"

using namespace BPMN;

SignalBoundaryEvent::SignalBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : BoundaryEvent(boundaryEvent,parent)
  , Node(boundaryEvent,parent)
  , CatchEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

