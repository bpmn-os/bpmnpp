#include "UntypedEndEvent.h"

using namespace BPMN;

UntypedEndEvent::UntypedEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , FlowNode(throwEvent,parent)
  , ThrowEvent(throwEvent,parent)
{
}

