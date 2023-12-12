#include "EscalationStartEvent.h"

using namespace BPMN;

EscalationStartEvent::EscalationStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent)
  : Node(startEvent)
  , CatchEvent(startEvent,parent)
  , TypedStartEvent(startEvent,parent)
  , element(startEvent)
{
}

