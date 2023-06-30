#include "Activity.h"

using namespace BPMN;

Activity::Activity(XML::bpmn::tActivity* activity, Scope* parent)
  : FlowNode(activity,parent)
  , Node(activity)
  , element(activity)
{
}

