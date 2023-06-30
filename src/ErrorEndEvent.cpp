#include "ErrorEndEvent.h"

using namespace BPMN;

ErrorEndEvent::ErrorEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : ThrowEvent(throwEvent,parent)
  , Node(throwEvent)
  , element(throwEvent)
{
}

