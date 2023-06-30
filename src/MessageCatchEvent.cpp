#include "MessageCatchEvent.h"

using namespace BPMN;

MessageCatchEvent::MessageCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : CatchEvent(catchEvent,parent)
  , Node(catchEvent)
  , element(catchEvent)
{
}

