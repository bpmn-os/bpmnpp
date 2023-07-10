#include "MessageCatchEvent.h"

using namespace BPMN;

MessageCatchEvent::MessageCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , CatchEvent(catchEvent,parent)
  , element(catchEvent)
{
}

