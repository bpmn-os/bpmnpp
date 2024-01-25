#include "LinkTargetEvent.h"
#include "xml/bpmn/tLinkEventDefinition.h"

using namespace BPMN;

LinkTargetEvent::LinkTargetEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , FlowNode(catchEvent,parent)
  , CatchEvent(catchEvent,parent)
  , linkName (element->getRequiredChild<XML::bpmn::tLinkEventDefinition>().name.value)
{
  // use node name as fallback
  if ( linkName.empty() && name.has_value() ) {
    linkName = name.value();
  }
}

