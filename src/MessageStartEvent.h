#ifndef BPMN_MessageStartEvent_H
#define BPMN_MessageStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tStartEvent.h"
#include "MessageCatchEvent.h"
#include "TypedStartEvent.h"

namespace BPMN {

class MessageStartEvent : public MessageCatchEvent, public TypedStartEvent {
  friend class Model;
public:
  MessageStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);

  XML::bpmn::tStartEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_MessageStartEvent_H
