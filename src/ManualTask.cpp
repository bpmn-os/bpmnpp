#include "ManualTask.h"

using namespace BPMN;

ManualTask::ManualTask(XML::bpmn::tManualTask* manualTask, Scope* parent)
  : Task(manualTask,parent)
  , Node(manualTask,parent)
  , element(manualTask)
{
}

