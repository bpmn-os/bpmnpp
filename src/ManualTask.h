#ifndef BPMN_ManualTask_H
#define BPMN_ManualTask_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tManualTask.h"
#include "Task.h"

namespace BPMN {

class ManualTask : public Task {
  friend class Model;
public:
  ManualTask(XML::bpmn::tManualTask* manualTask, Scope* parent);

  XML::bpmn::tManualTask* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ManualTask_H
