#ifndef BPMN_LinkSourceEvent_H
#define BPMN_LinkSourceEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

class LinkSourceEvent : public ThrowEvent {
  friend class Model;
public:
  LinkSourceEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  XML::bpmn::tThrowEvent* element;
  std::string linkName;
  FlowNode* target; 
protected:
};

} // namespace BPMN

#endif // BPMN_LinkSourceEvent_H
