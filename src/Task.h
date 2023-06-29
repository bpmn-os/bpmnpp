#ifndef BPMN_Task_H
#define BPMN_Task_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tTask.h"
#include "Activity.h"

namespace BPMN {

class Task : public Activity {
  friend class Model;
public:
  Task(XML::bpmn::tTask* task, Scope* parent);

  XML::bpmn::tTask* element;
protected:
};

} // namespace BPMN

#endif // BPMN_Task_H
