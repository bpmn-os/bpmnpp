#include "ConditionalBoundaryEvent.h"

using namespace BPMN;

ConditionalBoundaryEvent::ConditionalBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : Node(boundaryEvent)
  , FlowNode(boundaryEvent,parent)
  , CatchEvent(boundaryEvent,parent)
  , ConditionalCatchEvent(boundaryEvent,parent)
  , BoundaryEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

