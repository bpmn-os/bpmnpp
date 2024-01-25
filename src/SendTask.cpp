#include "SendTask.h"

using namespace BPMN;

SendTask::SendTask(XML::bpmn::tSendTask* sendTask, Scope* parent)
  : Node(sendTask)
  , FlowNode(sendTask,parent)
  , Task(sendTask,parent)
  , MessageThrowEvent(nullptr,parent)
  , element(sendTask)
{
}

