#include "UntypedEndEvent.h"

using namespace BPMN;

UntypedEndEvent::UntypedEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , ThrowEvent(throwEvent,parent)
{
}

