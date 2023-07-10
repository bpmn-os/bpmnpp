#include "CancelEndEvent.h"

using namespace BPMN;

CancelEndEvent::CancelEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , ThrowEvent(throwEvent,parent)
  , element(throwEvent)
{
}

