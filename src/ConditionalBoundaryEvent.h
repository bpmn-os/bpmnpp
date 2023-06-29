#ifndef BPMN_ConditionalBoundaryEvent_H
#define BPMN_ConditionalBoundaryEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tBoundaryEvent.h"
#include "BoundaryEvent.h"

namespace BPMN {

class ConditionalBoundaryEvent : virtual public BoundaryEvent, virtual public CatchEvent {
  friend class Model;
public:
  ConditionalBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);

  XML::bpmn::tBoundaryEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ConditionalBoundaryEvent_H
