#include "SendTask.h"

using namespace BPMN;

SendTask::SendTask(XML::bpmn::tSendTask* sendTask, Scope* parent)
  : Node(sendTask)
  , Task(sendTask,parent)
  , element(sendTask)
{
}

