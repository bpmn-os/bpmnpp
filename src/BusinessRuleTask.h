#ifndef BPMN_BusinessRuleTask_H
#define BPMN_BusinessRuleTask_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tBusinessRuleTask.h"
#include "Task.h"

namespace BPMN {

class BusinessRuleTask : public Task {
  friend class Model;
public:
  BusinessRuleTask(XML::bpmn::tBusinessRuleTask* businessRuleTask, Scope* parent);

  XML::bpmn::tBusinessRuleTask* element;
protected:
};

} // namespace BPMN

#endif // BPMN_BusinessRuleTask_H
