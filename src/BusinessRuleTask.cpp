#include "BusinessRuleTask.h"

using namespace BPMN;

BusinessRuleTask::BusinessRuleTask(XML::bpmn::tBusinessRuleTask* businessRuleTask, Scope* parent)
  : Task(businessRuleTask,parent)
  , Node(businessRuleTask)
  , element(businessRuleTask)
{
}

