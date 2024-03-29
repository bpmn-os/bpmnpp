#include "ConditionalStartEvent.h"

using namespace BPMN;

ConditionalStartEvent::ConditionalStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent)
  : Node(startEvent)
  , FlowNode(startEvent,parent)
  , CatchEvent(startEvent,parent)
  , ConditionalCatchEvent(startEvent,parent)
  , TypedStartEvent(startEvent,parent)
  , element(startEvent)
{
}

