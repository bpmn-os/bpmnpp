#include "ScriptTask.h"

using namespace BPMN;

ScriptTask::ScriptTask(XML::bpmn::tScriptTask* scriptTask, Scope* parent)
  : Node(scriptTask)
  , Task(scriptTask,parent)
  , element(scriptTask)
{
}

