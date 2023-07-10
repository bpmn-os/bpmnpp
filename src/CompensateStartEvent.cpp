#include "CompensateStartEvent.h"

using namespace BPMN;

CompensateStartEvent::CompensateStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , CatchEvent(catchEvent,parent)
  , element(catchEvent)
{
}

