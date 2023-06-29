#include "SignalThrowEvent.h"

using namespace BPMN;

SignalThrowEvent::SignalThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : ThrowEvent(throwEvent,parent)
  , Node(throwEvent,parent)
  , element(throwEvent)
{
}

