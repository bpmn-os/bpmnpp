#ifndef BPMN_EscalationThrowEvent_H
#define BPMN_EscalationThrowEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

class EscalationThrowEvent : public ThrowEvent {
  friend class Model;
public:
  EscalationThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
};

} // namespace BPMN

#endif // BPMN_EscalationThrowEvent_H
