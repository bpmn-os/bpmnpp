#include "CallActivity.h"

using namespace BPMN;

CallActivity::CallActivity(XML::bpmn::tCallActivity* callActivity, Scope* parent)
  : Node(callActivity)
  , Activity(callActivity,parent)
  , element(callActivity)
{
}

