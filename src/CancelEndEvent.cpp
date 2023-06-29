#include "CancelEndEvent.h"

using namespace BPMN;

CancelEndEvent::CancelEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : ThrowEvent(throwEvent,parent)
  , Node(throwEvent,parent)
  , element(throwEvent)
{
}

