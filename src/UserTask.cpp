#include "UserTask.h"

using namespace BPMN;

UserTask::UserTask(XML::bpmn::tUserTask* userTask, Scope* parent)
  : Node(userTask)
  , Task(userTask,parent)
  , element(userTask)
{
}

