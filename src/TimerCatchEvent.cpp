#include "TimerCatchEvent.h"

using namespace BPMN;

TimerCatchEvent::TimerCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , CatchEvent(catchEvent,parent)
  , element(catchEvent)
{
}

