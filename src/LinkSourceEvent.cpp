#include "LinkSourceEvent.h"
#include "xml/bpmn/tLinkEventDefinition.h"

using namespace BPMN;

LinkSourceEvent::LinkSourceEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent)
  : Node(throwEvent)
  , ThrowEvent(throwEvent,parent)
  , element(throwEvent)
  , linkName (element->getRequiredChild<XML::bpmn::tLinkEventDefinition>().name.value)
  , target(nullptr)
{
  // use node name as fallback
  if ( linkName.empty() && name.has_value() ) {
    linkName = name.value();
  }
}

