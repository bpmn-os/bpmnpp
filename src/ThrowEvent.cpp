#include "ThrowEvent.h"

using namespace BPMN;

ThrowEvent::ThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Event(throwEvent,parent)
  , Node(throwEvent)
  , element(throwEvent)
{
}

