#include "MessageThrowEvent.h"

using namespace BPMN;

MessageThrowEvent::MessageThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : ThrowEvent(throwEvent,parent)
  , Node(throwEvent,parent)
  , element(throwEvent)
{
}

