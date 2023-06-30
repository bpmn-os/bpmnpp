#include "MessageBoundaryEvent.h"

using namespace BPMN;

MessageBoundaryEvent::MessageBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : BoundaryEvent(boundaryEvent,parent)
  , Node(boundaryEvent)
  , CatchEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

