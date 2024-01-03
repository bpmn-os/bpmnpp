#ifndef BPMN_SignalThrowEvent_H
#define BPMN_SignalThrowEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

class SignalThrowEvent : public ThrowEvent {
  friend class Model;
public:
  SignalThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
};

} // namespace BPMN

#endif // BPMN_SignalThrowEvent_H
