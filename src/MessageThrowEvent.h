#ifndef BPMN_MessageThrowEvent_H
#define BPMN_MessageThrowEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

class MessageThrowEvent : public ThrowEvent {
  friend class Model;
public:
  MessageThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);

  XML::bpmn::tThrowEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_MessageThrowEvent_H
