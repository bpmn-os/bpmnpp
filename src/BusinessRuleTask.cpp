#include "BusinessRuleTask.h"

using namespace BPMN;

BusinessRuleTask::BusinessRuleTask(XML::bpmn::tBusinessRuleTask* businessRuleTask, Scope* parent)
  : Node(businessRuleTask)
  , Task(businessRuleTask,parent)
  , element(businessRuleTask)
{
}

