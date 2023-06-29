#ifndef BPMN_TerminateEvent_H
#define BPMN_TerminateEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

class TerminateEvent : public ThrowEvent {
  friend class Model;
public:
  TerminateEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);

  XML::bpmn::tThrowEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_TerminateEvent_H
