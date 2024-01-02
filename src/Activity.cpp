#include "Activity.h"

using namespace BPMN;

Activity::Activity(XML::bpmn::tActivity* activity, Scope* parent)
  : Node(activity)
  , FlowNode(activity,parent)
  , compensatedBy(nullptr)
  , element(activity)
{
}

