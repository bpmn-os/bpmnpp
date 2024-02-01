#include "AdHocSubProcess.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

AdHocSubProcess::AdHocSubProcess(XML::bpmn::tAdHocSubProcess* adHocSubProcess, Scope* parent)
  : Node(adHocSubProcess)
  , FlowNode(adHocSubProcess,parent)
  , Activity(adHocSubProcess,parent)
  , Scope(adHocSubProcess)
  , isSequential(false)
  , element(adHocSubProcess)
{
  if ( adHocSubProcess->ordering.has_value() ) {
    isSequential = ( adHocSubProcess->ordering.value().get().value.value == "Sequential" );
  }
}

