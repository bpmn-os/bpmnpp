#include "Activity.h"

using namespace BPMN;

Activity::Activity(XML::bpmn::tActivity* activity, Scope* parent)
  : Node(activity)
  , FlowNode(activity,parent)
  , compensatedBy(nullptr)
  , isForCompensation(activity->isForCompensation.has_value() && activity->isForCompensation.value().get().value)
  , element(activity)
{
}

