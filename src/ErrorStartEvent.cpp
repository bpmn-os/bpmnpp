#include "ErrorStartEvent.h"

using namespace BPMN;

ErrorStartEvent::ErrorStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : CatchEvent(catchEvent,parent)
  , Node(catchEvent,parent)
  , element(catchEvent)
{
}

