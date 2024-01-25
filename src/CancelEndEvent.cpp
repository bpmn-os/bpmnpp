#include "CancelEndEvent.h"

using namespace BPMN;

CancelEndEvent::CancelEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , FlowNode(throwEvent,parent)
  , ThrowEvent(throwEvent,parent)
{
}

