#include "Event.h"

using namespace BPMN;

Event::Event(XML::bpmn::tEvent* event, Scope* parent)
  : FlowNode(event,parent)
  , Node(event,parent)
  , element(event)
{
}

