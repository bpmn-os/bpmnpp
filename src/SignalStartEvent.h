#ifndef BPMN_SignalStartEvent_H
#define BPMN_SignalStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tStartEvent.h"
#include "SignalCatchEvent.h"
#include "TypedStartEvent.h"

namespace BPMN {

class SignalStartEvent : public SignalCatchEvent, public TypedStartEvent {
  friend class Model;
public:
  SignalStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
  XML::bpmn::tStartEvent* element;
};

} // namespace BPMN

#endif // BPMN_SignalStartEvent_H
