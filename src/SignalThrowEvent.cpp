#include "SignalThrowEvent.h"

using namespace BPMN;

SignalThrowEvent::SignalThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , ThrowEvent(throwEvent,parent)
{
}

