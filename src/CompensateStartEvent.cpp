#include "CompensateStartEvent.h"

using namespace BPMN;

CompensateStartEvent::CompensateStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : CatchEvent(catchEvent,parent)
  , Node(catchEvent,parent)
  , element(catchEvent)
{
}

