#ifndef BPMN_MessageBoundaryEvent_H
#define BPMN_MessageBoundaryEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tBoundaryEvent.h"
#include "MessageCatchEvent.h"
#include "BoundaryEvent.h"

namespace BPMN {

class MessageBoundaryEvent : public MessageCatchEvent, public BoundaryEvent {
  friend class Model;
public:
  MessageBoundaryEvent(XML::bpmn::tBoundaryEvent* boundaryEvent, Scope* parent);
  XML::bpmn::tBoundaryEvent* element;
};

} // namespace BPMN

#endif // BPMN_MessageBoundaryEvent_H
