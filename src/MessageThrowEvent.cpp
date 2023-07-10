#include "MessageThrowEvent.h"

using namespace BPMN;

MessageThrowEvent::MessageThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , ThrowEvent(throwEvent,parent)
  , element(throwEvent)
{
}

