#include "CompensateThrowEvent.h"

using namespace BPMN;

CompensateThrowEvent::CompensateThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : ThrowEvent(throwEvent,parent)
  , Node(throwEvent,parent)
  , element(throwEvent)
{
}

