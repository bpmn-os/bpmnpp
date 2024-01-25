#include "BusinessRuleTask.h"

using namespace BPMN;

BusinessRuleTask::BusinessRuleTask(XML::bpmn::tBusinessRuleTask* businessRuleTask, Scope* parent)
  : Node(businessRuleTask)
  , FlowNode(businessRuleTask,parent)
  , Task(businessRuleTask,parent)
  , element(businessRuleTask)
{
}

