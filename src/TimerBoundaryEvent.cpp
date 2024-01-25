#include "TimerBoundaryEvent.h"

using namespace BPMN;

TimerBoundaryEvent::TimerBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : Node(boundaryEvent)
  , FlowNode(boundaryEvent,parent)
  , CatchEvent(boundaryEvent,parent)
  , TimerCatchEvent(boundaryEvent,parent)
  , BoundaryEvent(boundaryEvent,parent)
  , element(boundaryEvent)
{
}

