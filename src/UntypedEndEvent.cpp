#include "UntypedEndEvent.h"

using namespace BPMN;

UntypedEndEvent::UntypedEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : ThrowEvent(throwEvent,parent)
  , Node(throwEvent,parent)
  , element(throwEvent)
{
}

