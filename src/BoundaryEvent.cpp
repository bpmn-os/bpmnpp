#include "BoundaryEvent.h"

using namespace BPMN;

BoundaryEvent::BoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent)
  : Node(boundaryEvent)
  , FlowNode(boundaryEvent,parent)
  , CatchEvent(boundaryEvent,parent)
  , isInterrupting(element->get<XML::bpmn::tBoundaryEvent>()->cancelActivity.has_value() ? (bool)element->get<XML::bpmn::tBoundaryEvent>()->cancelActivity.value().get().value : true)
  , attachedTo(resolveReference())
{
}

Activity* BoundaryEvent::resolveReference() {
  const std::string& reference = element->get<XML::bpmn::tBoundaryEvent>()->attachedToRef.value;
  for ( auto& sibling : parent->flowNodes ) {
    if ( sibling->id == reference ) {
      Activity* activity = sibling->as<Activity>();
      activity->boundaryEvents.push_back(this);
      return activity;
    }
  }
  throw std::runtime_error("BoundaryEvent: cannot resolve reference '" + reference + "' for boundary event '" + id + "'");
}

