#include "AdHocSubProcess.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

AdHocSubProcess::AdHocSubProcess(XML::bpmn::tAdHocSubProcess* adHocSubProcess, Scope* parent)
  : SubProcess(adHocSubProcess,parent)
  , Node(adHocSubProcess)
  , element(adHocSubProcess)
{
}

