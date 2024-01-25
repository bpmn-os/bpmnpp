#include "ManualTask.h"

using namespace BPMN;

ManualTask::ManualTask(XML::bpmn::tManualTask* manualTask, Scope* parent)
  : Node(manualTask)
  , FlowNode(manualTask,parent)
  , Task(manualTask,parent)
  , element(manualTask)
{
}

