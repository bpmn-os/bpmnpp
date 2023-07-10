#include "SignalCatchEvent.h"

using namespace BPMN;

SignalCatchEvent::SignalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , CatchEvent(catchEvent,parent)
  , element(catchEvent)
{
}

