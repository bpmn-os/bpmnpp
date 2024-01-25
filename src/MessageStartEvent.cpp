#include "MessageStartEvent.h"

using namespace BPMN;

MessageStartEvent::MessageStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent)
  : Node(startEvent)
  , FlowNode(startEvent,parent)
  , CatchEvent(startEvent,parent)
  , MessageCatchEvent(startEvent,parent)
  , TypedStartEvent(startEvent,parent)
  , element(startEvent)
{
}

