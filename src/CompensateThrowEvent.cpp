#include "CompensateThrowEvent.h"

using namespace BPMN;

CompensateThrowEvent::CompensateThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , FlowNode(throwEvent,parent)
  , ThrowEvent(throwEvent,parent)
  , activity(nullptr)
{
}

