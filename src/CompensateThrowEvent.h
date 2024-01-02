#ifndef BPMN_CompensateThrowEvent_H
#define BPMN_CompensateThrowEvent_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tThrowEvent.h"
#include "ThrowEvent.h"

namespace BPMN {

/**
 * @note It is assumed that `waitForCompletion` is `true`
 * @note If `activity` is `nullptr` then each completed Activity in relevant Scope is compensated
 **/
class CompensateThrowEvent : public ThrowEvent {
  friend class Model;
public:
  CompensateThrowEvent(XML::bpmn::tThrowEvent* throwEvent, Scope* parent);
  FlowNode* activity; ///< Activity to be compensated
  XML::bpmn::tThrowEvent* element;
protected:
};

} // namespace BPMN

#endif // BPMN_CompensateThrowEvent_H
