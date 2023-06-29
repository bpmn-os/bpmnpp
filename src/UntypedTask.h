#ifndef BPMN_UntypedTask_H
#define BPMN_UntypedTask_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tTask.h"
#include "Task.h"

namespace BPMN {

class UntypedTask : public Task {
  friend class Model;
public:
  UntypedTask(XML::bpmn::tTask* task, Scope* parent);

  XML::bpmn::tTask* element;
protected:
};

} // namespace BPMN

#endif // BPMN_UntypedTask_H
