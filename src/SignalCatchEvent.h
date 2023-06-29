#ifndef BPMN_SignalCatchEvent_H
#define BPMN_SignalCatchEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCatchEvent.h"
#include "CatchEvent.h"

namespace BPMN {

class SignalCatchEvent : virtual public CatchEvent {
  friend class Model;
public:
  SignalCatchEvent(XML::bpmn::tCatchEvent* catchEvent, Scope* parent);

  XML::bpmn::tCatchEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_SignalCatchEvent_H
