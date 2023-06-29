#include "TimerCatchEvent.h"

using namespace BPMN;

TimerCatchEvent::TimerCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : CatchEvent(catchEvent,parent)
  , Node(catchEvent,parent)
  , element(catchEvent)
{
}

