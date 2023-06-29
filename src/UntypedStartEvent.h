#ifndef BPMN_UntypedStartEvent_H
#define BPMN_UntypedStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "CatchEvent.h"

namespace BPMN {

class UntypedStartEvent : virtual public CatchEvent {
  friend class Model;
public:
  UntypedStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);

  XML::bpmn::tCatchEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_UntypedStartEvent_H
