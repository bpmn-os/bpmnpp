#ifndef BPMN_ScriptTask_H
#define BPMN_ScriptTask_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tScriptTask.h"
#include "Task.h"

namespace BPMN {

class ScriptTask : public Task {
  friend class Model;
public:
  ScriptTask(XML::bpmn::tScriptTask* scriptTask, Scope* parent);

  XML::bpmn::tScriptTask* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ScriptTask_H
