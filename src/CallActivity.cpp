#include "CallActivity.h"

using namespace BPMN;

CallActivity::CallActivity(XML::bpmn::tCallActivity* callActivity, Scope* parent)
  : Activity(callActivity,parent)
  , Node(callActivity,parent)
  , element(callActivity)
{
}

