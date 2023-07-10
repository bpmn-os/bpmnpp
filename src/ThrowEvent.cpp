#include "ThrowEvent.h"

using namespace BPMN;

ThrowEvent::ThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , Event(throwEvent,parent)
  , element(throwEvent)
{
}

