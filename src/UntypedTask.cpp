#include "UntypedTask.h"

using namespace BPMN;

UntypedTask::UntypedTask(XML::bpmn::tTask* task, Scope* parent)
  : Task(task,parent)
  , Node(task,parent)
  , element(task)
{
}

