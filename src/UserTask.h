#ifndef BPMN_UserTask_H
#define BPMN_UserTask_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tUserTask.h"
#include "Task.h"

namespace BPMN {

class UserTask : public Task {
  friend class Model;
public:
  UserTask(XML::bpmn::tUserTask* userTask, Scope* parent);

  XML::bpmn::tUserTask* element;
protected:
};

} // namespace BPMN

#endif // BPMN_UserTask_H
