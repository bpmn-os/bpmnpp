#ifndef BPMN_CompensateBoundaryEvent_H
#define BPMN_CompensateBoundaryEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tBoundaryEvent.h"
#include "BoundaryEvent.h"

namespace BPMN {

class CompensateBoundaryEvent : virtual public BoundaryEvent, virtual public CatchEvent {
  friend class Model;
public:
  CompensateBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);

  XML::bpmn::tBoundaryEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_CompensateBoundaryEvent_H
