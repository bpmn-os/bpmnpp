#include "ScriptTask.h"

using namespace BPMN;

ScriptTask::ScriptTask(XML::bpmn::tScriptTask* scriptTask, Scope* parent)
  : Task(scriptTask,parent)
  , Node(scriptTask)
  , element(scriptTask)
{
}

