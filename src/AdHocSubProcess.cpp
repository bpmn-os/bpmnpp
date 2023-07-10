#include "AdHocSubProcess.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

AdHocSubProcess::AdHocSubProcess(XML::bpmn::tAdHocSubProcess* adHocSubProcess, Scope* parent)
  : Node(adHocSubProcess)
  , SubProcess(adHocSubProcess,parent)
  , element(adHocSubProcess)
{
}

