#include "ReceiveTask.h"

using namespace BPMN;

ReceiveTask::ReceiveTask(XML::bpmn::tReceiveTask* receiveTask, Scope* parent)
  : Node(receiveTask)
  , FlowNode(receiveTask,parent)
  , CatchEvent(nullptr,parent)
  , Task(receiveTask,parent)
  , MessageCatchEvent(nullptr,parent)
  , element(receiveTask)
{
}

