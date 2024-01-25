#include "EscalationThrowEvent.h"

using namespace BPMN;

EscalationThrowEvent::EscalationThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , FlowNode(throwEvent,parent)
  , ThrowEvent(throwEvent,parent)
{
}

