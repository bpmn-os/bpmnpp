#include "AdHocSubProcess.h"

using namespace BPMN;

AdHocSubProcess::AdHocSubProcess(XML::bpmn::tAdHocSubProcess* adHocSubProcess, Scope* parent)
  : SubProcess(adHocSubProcess,parent)
  , Node(adHocSubProcess)
  , element(adHocSubProcess)
{
}

