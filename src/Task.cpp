#include "Task.h"

using namespace BPMN;

Task::Task(XML::bpmn::tTask* task, Scope* parent)
  : Node(task)
  , Activity(task,parent)
  , element(task)
{
}

