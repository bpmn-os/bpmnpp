#ifndef BPMN_CompensateStartEvent_H
#define BPMN_CompensateStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tStartEvent.h"
#include "TypedStartEvent.h"

namespace BPMN {

class CompensateStartEvent : public TypedStartEvent {
  friend class Model;
public:
  CompensateStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
};

} // namespace BPMN

#endif // BPMN_CompensateStartEvent_H
