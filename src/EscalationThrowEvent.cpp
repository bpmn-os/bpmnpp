#include "EscalationThrowEvent.h"

using namespace BPMN;

EscalationThrowEvent::EscalationThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , ThrowEvent(throwEvent,parent)
  , element(throwEvent)
{
}

