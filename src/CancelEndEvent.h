#ifndef BPMN_CancelEndEvent_H
#define BPMN_CancelEndEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

class CancelEndEvent : public ThrowEvent {
  friend class Model;
public:
  CancelEndEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
};

} // namespace BPMN

#endif // BPMN_CancelEndEvent_H
