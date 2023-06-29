#include "Task.h"

using namespace BPMN;

Task::Task(XML::bpmn::tTask* task, Scope* parent)
  : Activity(task,parent)
  , Node(task,parent)
  , element(task)
{
}

