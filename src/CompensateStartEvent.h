#ifndef BPMN_CompensateStartEvent_H
#define BPMN_CompensateStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "CatchEvent.h"

namespace BPMN {

class CompensateStartEvent : virtual public CatchEvent {
  friend class Model;
public:
  CompensateStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);

  XML::bpmn::tCatchEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_CompensateStartEvent_H
