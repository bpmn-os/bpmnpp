#include "ManualTask.h"

using namespace BPMN;

ManualTask::ManualTask(XML::bpmn::tManualTask* manualTask, Scope* parent)
  : Node(manualTask)
  , Task(manualTask,parent)
  , element(manualTask)
{
}

