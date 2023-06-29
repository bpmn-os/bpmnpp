#include "EscalationThrowEvent.h"

using namespace BPMN;

EscalationThrowEvent::EscalationThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : ThrowEvent(throwEvent,parent)
  , Node(throwEvent,parent)
  , element(throwEvent)
{
}

