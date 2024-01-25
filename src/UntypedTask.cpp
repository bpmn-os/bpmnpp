#include "UntypedTask.h"

using namespace BPMN;

UntypedTask::UntypedTask(XML::bpmn::tTask* task, Scope* parent)
  : Node(task)
  , FlowNode(task,parent)
  , Task(task,parent)
{
}

