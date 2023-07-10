#include "ErrorBoundaryEvent.h"

using namespace BPMN;

ErrorBoundaryEvent::ErrorBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : Node(boundaryEvent)
  , CatchEvent(boundaryEvent,parent)
  , BoundaryEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

