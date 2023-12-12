#ifndef BPMN_ConditionalStartEvent_H
#define BPMN_ConditionalStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tStartEvent.h"
#include "ConditionalCatchEvent.h"
#include "TypedStartEvent.h"

namespace BPMN {

class ConditionalStartEvent : public ConditionalCatchEvent, public TypedStartEvent {
  friend class Model;
public:
  ConditionalStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);

  XML::bpmn::tStartEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ConditionalStartEvent_H
