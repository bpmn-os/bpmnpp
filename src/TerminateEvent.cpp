#include "TerminateEvent.h"

using namespace BPMN;

TerminateEvent::TerminateEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : ThrowEvent(throwEvent,parent)
  , Node(throwEvent)
  , element(throwEvent)
{
}

