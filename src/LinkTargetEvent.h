#ifndef BPMN_LinkTargetEvent_H
#define BPMN_LinkTargetEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "CatchEvent.h"

namespace BPMN {

/**
 * @attention If no `linkName` is given, it is set to `name` attribute if this is given.
 * The sources are determined based on the `linkName`.
 */
class LinkTargetEvent : virtual public CatchEvent {
  friend class Model;
public:
  LinkTargetEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  std::string linkName;
  std::vector<FlowNode*> sources;
};

} // namespace BPMN

#endif // BPMN_LinkTargetEvent_H
