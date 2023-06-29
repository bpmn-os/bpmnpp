#ifndef BPMN_ReceiveTask_H
#define BPMN_ReceiveTask_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tReceiveTask.h"
#include "Task.h"

namespace BPMN {

class ReceiveTask : public Task {
  friend class Model;
public:
  ReceiveTask(XML::bpmn::tReceiveTask* receiveTask, Scope* parent);

  XML::bpmn::tReceiveTask* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ReceiveTask_H
