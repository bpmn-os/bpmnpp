#include "TerminateEvent.h"

using namespace BPMN;

TerminateEvent::TerminateEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , ThrowEvent(throwEvent,parent)
  , element(throwEvent)
{
}

