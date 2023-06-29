#ifndef BPMN_SignalBoundaryEvent_H
#define BPMN_SignalBoundaryEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tBoundaryEvent.h"
#include "BoundaryEvent.h"

namespace BPMN {

class SignalBoundaryEvent : virtual public BoundaryEvent, virtual public CatchEvent {
  friend class Model;
public:
  SignalBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);

  XML::bpmn::tBoundaryEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_SignalBoundaryEvent_H
