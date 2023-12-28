#include "LinkTargetEvent.h"
#include "xml/bpmn/tLinkEventDefinition.h"

using namespace BPMN;

LinkTargetEvent::LinkTargetEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent)
  : Node(catchEvent)
  , CatchEvent(catchEvent,parent)
  , element(catchEvent)
  , linkName (element->getRequiredChild<XML::bpmn::tLinkEventDefinition>().name.value)
{
  // use node name as fallback
  if ( linkName.empty() && name.has_value() ) {
    linkName = name.value();
  }
}

