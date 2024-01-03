#include "ConditionalCatchEvent.h"

using namespace BPMN;

ConditionalCatchEvent::ConditionalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , CatchEvent(catchEvent,parent)
{
}

