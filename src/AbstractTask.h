#ifndef BPMN_AbstractTask_H
#define BPMN_AbstractTask_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tTask.h"
#include "Task.h"

namespace BPMN {

class AbstractTask : public Task {
  friend class Model;
public:
  AbstractTask(XML::bpmn::tTask* task, Scope* parent);
};

} // namespace BPMN

#endif // BPMN_AbstractTask_H
