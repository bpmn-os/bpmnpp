#include "BoundaryEvent.h"

using namespace BPMN;

BoundaryEvent::BoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : Node(boundaryEvent)
  , CatchEvent(boundaryEvent,parent)
  , attachedTo(resolveReference())
{
}

Activity* BoundaryEvent::resolveReference() {
  const std::string& reference = element->get<XML::bpmn::tBoundaryEvent>()->attachedToRef;
  for ( auto& sibling : parent->flowNodes ) {
    if ( sibling->id == reference ) {
      Activity* activity = sibling->as<Activity>();
      activity->boundaryEvents.push_back(this);
      return activity;
    }
  }
  throw std::runtime_error("BoundaryEvent: cannot resolve reference");
}

