#include "CompensateStartEvent.h"

using namespace BPMN;

CompensateStartEvent::CompensateStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent)
  : Node(startEvent)
  , FlowNode(startEvent,parent)
  , CatchEvent(startEvent,parent)
  , TypedStartEvent(startEvent,parent)
{
}

