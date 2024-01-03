#ifndef BPMN_EscalationStartEvent_H
#define BPMN_EscalationStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tStartEvent.h"
#include "TypedStartEvent.h"

namespace BPMN {

class EscalationStartEvent : public TypedStartEvent {
  friend class Model;
public:
  EscalationStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
};

} // namespace BPMN

#endif // BPMN_EscalationStartEvent_H
