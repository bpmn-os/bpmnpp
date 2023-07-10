#include "EscalationStartEvent.h"

using namespace BPMN;

EscalationStartEvent::EscalationStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , CatchEvent(catchEvent,parent)
  , element(catchEvent)
{
}

