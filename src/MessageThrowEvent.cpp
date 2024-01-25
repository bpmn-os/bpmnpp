#include "MessageThrowEvent.h"

using namespace BPMN;

MessageThrowEvent::MessageThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , FlowNode(throwEvent,parent)
  , ThrowEvent(throwEvent,parent)
{
}

