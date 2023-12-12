#include "TypedStartEvent.h"

using namespace BPMN;

TypedStartEvent::TypedStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent)
  : Node(startEvent)
  , CatchEvent(startEvent,parent)
  , isInterrupting(element->get<XML::bpmn::tStartEvent>()->isInterrupting.has_value() ? (bool)element->get<XML::bpmn::tStartEvent>()->isInterrupting.value().get().value : true)
{
}


