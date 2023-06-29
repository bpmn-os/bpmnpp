#include "EscalationStartEvent.h"

using namespace BPMN;

EscalationStartEvent::EscalationStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : CatchEvent(catchEvent,parent)
  , Node(catchEvent,parent)
  , element(catchEvent)
{
}

