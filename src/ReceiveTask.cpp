#include "ReceiveTask.h"

using namespace BPMN;

ReceiveTask::ReceiveTask(XML::bpmn::tReceiveTask* receiveTask, Scope* parent)
  : Task(receiveTask,parent)
  , Node(receiveTask)
  , element(receiveTask)
{
}

