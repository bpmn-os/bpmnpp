#include "MessageBoundaryEvent.h"

using namespace BPMN;

MessageBoundaryEvent::MessageBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : Node(boundaryEvent)
  , CatchEvent(boundaryEvent,parent)
  , BoundaryEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

