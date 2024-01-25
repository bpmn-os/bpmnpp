#include "ScriptTask.h"

using namespace BPMN;

ScriptTask::ScriptTask(XML::bpmn::tScriptTask* scriptTask, Scope* parent)
  : Node(scriptTask)
  , FlowNode(scriptTask,parent)
  , Task(scriptTask,parent)
  , element(scriptTask)
{
}

