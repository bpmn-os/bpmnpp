#include "ConditionalCatchEvent.h"

using namespace BPMN;

ConditionalCatchEvent::ConditionalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : CatchEvent(catchEvent,parent)
  , Node(catchEvent)
  , element(catchEvent)
{
}

