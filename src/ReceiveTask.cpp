#include "ReceiveTask.h"

using namespace BPMN;

ReceiveTask::ReceiveTask(XML::bpmn::tReceiveTask* receiveTask, Scope* parent)
  : Node(receiveTask)
  , Task(receiveTask,parent)
  , element(receiveTask)
{
}

