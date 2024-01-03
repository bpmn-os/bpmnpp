#ifndef BPMN_EscalationBoundaryEvent_H
#define BPMN_EscalationBoundaryEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tBoundaryEvent.h"
#include "BoundaryEvent.h"

namespace BPMN {

class EscalationBoundaryEvent : virtual public BoundaryEvent, virtual public CatchEvent {
  friend class Model;
public:
  EscalationBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  XML::bpmn::tBoundaryEvent* element;
};

} // namespace BPMN

#endif // BPMN_EscalationBoundaryEvent_H
