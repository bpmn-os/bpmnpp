#include "CompensateThrowEvent.h"

using namespace BPMN;

CompensateThrowEvent::CompensateThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , ThrowEvent(throwEvent,parent)
  , element(throwEvent)
{
}

