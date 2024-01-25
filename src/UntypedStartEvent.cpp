#include "UntypedStartEvent.h"

using namespace BPMN;

UntypedStartEvent::UntypedStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , FlowNode(catchEvent,parent)
  , CatchEvent(catchEvent,parent)
{
}

