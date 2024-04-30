#include "AbstractTask.h"

using namespace BPMN;

AbstractTask::AbstractTask(XML::bpmn::tTask* task, Scope* parent)
  : Node(task)
  , FlowNode(task,parent)
  , Task(task,parent)
{
}

