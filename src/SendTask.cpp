#include "SendTask.h"

using namespace BPMN;

SendTask::SendTask(XML::bpmn::tSendTask* sendTask, Scope* parent)
  : Task(sendTask,parent)
  , Node(sendTask)
  , element(sendTask)
{
}

