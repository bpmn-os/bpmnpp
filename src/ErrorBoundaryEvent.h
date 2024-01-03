#ifndef BPMN_ErrorBoundaryEvent_H
#define BPMN_ErrorBoundaryEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tBoundaryEvent.h"
#include "BoundaryEvent.h"

namespace BPMN {

class ErrorBoundaryEvent : virtual public BoundaryEvent, virtual public CatchEvent {
  friend class Model;
public:
  ErrorBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  XML::bpmn::tBoundaryEvent* element;
};

} // namespace BPMN

#endif // BPMN_ErrorBoundaryEvent_H
