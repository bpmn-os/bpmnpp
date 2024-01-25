#include "MessageCatchEvent.h"

using namespace BPMN;

MessageCatchEvent::MessageCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , FlowNode(catchEvent,parent)
  , CatchEvent(catchEvent,parent)
{
}

