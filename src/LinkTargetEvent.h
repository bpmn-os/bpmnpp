#ifndef BPMN_LinkTargetEvent_H
#define BPMN_LinkTargetEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "CatchEvent.h"

namespace BPMN {

class LinkTargetEvent : virtual public CatchEvent {
  friend class Model;
public:
  LinkTargetEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);
  XML::bpmn::tCatchEvent* element;
  std::string linkName;
  std::vector<FlowNode*> sources;
protected:
};

} // namespace BPMN

#endif // BPMN_LinkTargetEvent_H
