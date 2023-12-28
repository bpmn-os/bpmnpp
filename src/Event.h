#ifndef BPMN_Event_H
#define BPMN_Event_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tEvent.h"
#include "FlowNode.h"

namespace BPMN {

/**
 * @attention Multiple event definitions are not yet supported.
 **/
class Event : public FlowNode {
  friend class Model;
public:
  Event(XML::bpmn::tEvent* event, Scope* parent);

  XML::bpmn::tEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_Event_H
