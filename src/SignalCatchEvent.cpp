#include "SignalCatchEvent.h"

using namespace BPMN;

SignalCatchEvent::SignalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : CatchEvent(catchEvent,parent)
  , Node(catchEvent,parent)
  , element(catchEvent)
{
}

