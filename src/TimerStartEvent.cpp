#include "TimerStartEvent.h"

using namespace BPMN;

TimerStartEvent::TimerStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent)
  : Node(startEvent)
  , CatchEvent(startEvent,parent)
  , TimerCatchEvent(startEvent,parent)
  , TypedStartEvent(startEvent,parent)
  , element(startEvent)
{
}

