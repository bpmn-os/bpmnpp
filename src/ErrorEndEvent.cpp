#include "ErrorEndEvent.h"

using namespace BPMN;

ErrorEndEvent::ErrorEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , FlowNode(throwEvent,parent)
  , ThrowEvent(throwEvent,parent)
{
}

