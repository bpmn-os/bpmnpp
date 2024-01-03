#ifndef BPMN_ErrorStartEvent_H
#define BPMN_ErrorStartEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tStartEvent.h"
#include "TypedStartEvent.h"

namespace BPMN {

class ErrorStartEvent : public TypedStartEvent {
  friend class Model;
public:
  ErrorStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
};

} // namespace BPMN

#endif // BPMN_ErrorStartEvent_H
