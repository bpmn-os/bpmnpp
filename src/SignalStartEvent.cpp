#include "SignalStartEvent.h"

using namespace BPMN;

SignalStartEvent::SignalStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent)
  : Node(startEvent)
  , FlowNode(startEvent,parent)
  , CatchEvent(startEvent,parent)
  , SignalCatchEvent(startEvent,parent)
  , TypedStartEvent(startEvent,parent)
  , element(startEvent)
{
}

