#ifndef BPMN_SendTask_H
#define BPMN_SendTask_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tSendTask.h"
#include "Task.h"

namespace BPMN {

class SendTask : public Task {
  friend class Model;
public:
  SendTask(XML::bpmn::tSendTask* sendTask, Scope* parent);

  XML::bpmn::tSendTask* element;
protected:
};

} // namespace BPMN

#endif // BPMN_SendTask_H
