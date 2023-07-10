#include "Event.h"

using namespace BPMN;

Event::Event(XML::bpmn::tEvent* event, Scope* parent)
  : Node(event)
  , FlowNode(event,parent)
  , element(event)
{
}

