#include "CallActivity.h"

using namespace BPMN;

CallActivity::CallActivity(XML::bpmn::tCallActivity* callActivity, Scope* parent)
  : Node(callActivity)
  , FlowNode(callActivity,parent)
  , Activity(callActivity,parent)
  , element(callActivity)
{
}

