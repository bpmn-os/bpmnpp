#ifndef BPMN_TypedStartEvent_H
#define BPMN_TypedStartEvent_H

#include "xml/bpmn/tStartEvent.h"
#include "Scope.h"
#include "CatchEvent.h"

namespace BPMN {

class Activity;

/**
 * @brief Base class for all start events with an event definition.
 */
class TypedStartEvent : virtual public CatchEvent {
  friend class Model;
public:
  TypedStartEvent(XML::bpmn::tStartEvent* startEvent, Scope* parent);
  bool isInterrupting;
};

} // namespace BPMN

#endif // BPMN_TypedStartEvent_H
