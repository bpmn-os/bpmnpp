#include "UntypedTask.h"

using namespace BPMN;

UntypedTask::UntypedTask(XML::bpmn::tTask* task, Scope* parent)
  : Node(task)
  , Task(task,parent)
{
}

