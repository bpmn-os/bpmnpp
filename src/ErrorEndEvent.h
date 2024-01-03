#ifndef BPMN_ErrorEndEvent_H
#define BPMN_ErrorEndEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

class ErrorEndEvent : public ThrowEvent {
  friend class Model;
public:
  ErrorEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
};

} // namespace BPMN

#endif // BPMN_ErrorEndEvent_H
