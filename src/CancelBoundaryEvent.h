#ifndef BPMN_CancelBoundaryEvent_H
#define BPMN_CancelBoundaryEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tBoundaryEvent.h"
#include "BoundaryEvent.h"

namespace BPMN {

class CancelBoundaryEvent : virtual public BoundaryEvent, virtual public CatchEvent {
  friend class Model;
public:
  CancelBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);

  XML::bpmn::tBoundaryEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_CancelBoundaryEvent_H
