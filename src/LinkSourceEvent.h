#ifndef BPMN_LinkSourceEvent_H
#define BPMN_LinkSourceEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

/**
 * @attention If no `linkName` is given, it is set to `name` attribute if this is given.
 * The target is determined based on the `linkName`.
 */
class LinkSourceEvent : public ThrowEvent {
  friend class Model;
public:
  LinkSourceEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  std::string linkName;
  FlowNode* target; 
};

} // namespace BPMN

#endif // BPMN_LinkSourceEvent_H
