#include "CatchEvent.h"

using namespace BPMN;

CatchEvent::CatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Event(catchEvent,parent)
  , Node(catchEvent)
  , element(catchEvent)
{
}

