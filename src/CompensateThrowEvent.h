#ifndef BPMN_CompensateThrowEvent_H
#define BPMN_CompensateThrowEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"
#include "Activity.h"

namespace BPMN {

/**
 * @note If @ref activity is `nullptr` then each completed Activity in relevant Scope has to be compensated.
 **/
class CompensateThrowEvent : public ThrowEvent {
  friend class Model;
public:
  CompensateThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  Activity* activity; ///< Activity to be compensated
};

} // namespace BPMN

#endif // BPMN_CompensateThrowEvent_H
