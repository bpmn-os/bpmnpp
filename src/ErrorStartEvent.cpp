#include "ErrorStartEvent.h"

using namespace BPMN;

ErrorStartEvent::ErrorStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , CatchEvent(catchEvent,parent)
  , element(catchEvent)
{
}

