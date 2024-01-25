#include "ErrorStartEvent.h"

using namespace BPMN;

ErrorStartEvent::ErrorStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent)
  : Node(startEvent)
  , FlowNode(startEvent,parent)
  , CatchEvent(startEvent,parent)
  , TypedStartEvent(startEvent,parent)
{
}

