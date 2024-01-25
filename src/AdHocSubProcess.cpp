#include "AdHocSubProcess.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

AdHocSubProcess::AdHocSubProcess(XML::bpmn::tAdHocSubProcess* adHocSubProcess, Scope* parent)
  : Node(adHocSubProcess)
  , FlowNode(adHocSubProcess,parent)
  , SubProcess(adHocSubProcess,parent)
  , element(adHocSubProcess)
{
}

