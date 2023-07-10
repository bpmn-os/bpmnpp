#include "CatchEvent.h"

using namespace BPMN;

CatchEvent::CatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , Event(catchEvent,parent)
  , element(catchEvent)
{
}

