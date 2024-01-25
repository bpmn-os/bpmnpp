#include "MessageBoundaryEvent.h"

using namespace BPMN;

MessageBoundaryEvent::MessageBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : Node(boundaryEvent)
  , FlowNode(boundaryEvent,parent)
  , CatchEvent(boundaryEvent,parent)
  , MessageCatchEvent(boundaryEvent,parent)
  , BoundaryEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

