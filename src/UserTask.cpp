#include "UserTask.h"

using namespace BPMN;

UserTask::UserTask(XML::bpmn::tUserTask* userTask, Scope* parent)
  : Task(userTask,parent)
  , Node(userTask)
  , element(userTask)
{
}

