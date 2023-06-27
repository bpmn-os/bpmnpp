#include "BoundaryEvent.h"
#include "xml/bpmn/tActivity.h"

using namespace BPMN;

BoundaryEvent::BoundaryEvent(XML::bpmn::tBoundaryEvent& boundaryEvent, Node* parentNode)
  : Node(boundaryEvent,parentNode)
  , attachedTo(resolveReference())
{
}

Node& BoundaryEvent::resolveReference() {
  const std::string& reference = element->get<XML::bpmn::tBoundaryEvent>()->attachedToRef;
  for ( auto& sibling : parentNode->childNodes ) {
    if ( sibling->id == reference ) {
      return *sibling;
    }
  }
  throw std::runtime_error("BoundaryEvent: cannot resolve reference");
}

