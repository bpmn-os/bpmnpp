#include "LinkSourceEvent.h"
#include "xml/bpmn/tLinkEventDefinition.h"

using namespace BPMN;

LinkSourceEvent::LinkSourceEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , FlowNode(throwEvent,parent)
  , ThrowEvent(throwEvent,parent)
  , linkName (element->getRequiredChild<XML::bpmn::tLinkEventDefinition>().name.value)
  , target(nullptr)
{
  if ( linkName.empty() && name.has_value() ) {
    linkName = name.value();
  }
}
