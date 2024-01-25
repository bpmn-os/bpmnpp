#include "ThrowEvent.h"

using namespace BPMN;

ThrowEvent::ThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , FlowNode(throwEvent,parent)
  , Event(throwEvent,parent)
  , element(throwEvent)
{
}

