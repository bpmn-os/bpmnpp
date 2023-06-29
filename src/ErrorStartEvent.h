#ifndef BPMN_ErrorStartEvent_H
#define BPMN_ErrorStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "CatchEvent.h"

namespace BPMN {

class ErrorStartEvent : virtual public CatchEvent {
  friend class Model;
public:
  ErrorStartEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);

  XML::bpmn::tCatchEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ErrorStartEvent_H
