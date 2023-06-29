#include "UntypedStartEvent.h"

using namespace BPMN;

UntypedStartEvent::UntypedStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : CatchEvent(catchEvent,parent)
  , Node(catchEvent,parent)
  , element(catchEvent)
{
}

