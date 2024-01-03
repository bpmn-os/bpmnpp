#ifndef BPMN_MessageCatchEvent_H
#define BPMN_MessageCatchEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "CatchEvent.h"

namespace BPMN {

class MessageCatchEvent : virtual public CatchEvent {
  friend class Model;
public:
  MessageCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
};

} // namespace BPMN

#endif // BPMN_MessageCatchEvent_H
