#ifndef BPMN_CompensateThrowEvent_H
#define BPMN_CompensateThrowEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

class CompensateThrowEvent : public ThrowEvent {
  friend class Model;
public:
  CompensateThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);

  XML::bpmn::tThrowEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_CompensateThrowEvent_H
