#ifndef BPMN_EscalationStartEvent_H
#define BPMN_EscalationStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "CatchEvent.h"

namespace BPMN {

class EscalationStartEvent : virtual public CatchEvent {
  friend class Model;
public:
  EscalationStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);

  XML::bpmn::tCatchEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_EscalationStartEvent_H
