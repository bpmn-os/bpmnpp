#ifndef BPMN_ConditionalCatchEvent_H
#define BPMN_ConditionalCatchEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "CatchEvent.h"

namespace BPMN {

class ConditionalCatchEvent : virtual public CatchEvent {
  friend class Model;
public:
  ConditionalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);

  XML::bpmn::tCatchEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ConditionalCatchEvent_H
