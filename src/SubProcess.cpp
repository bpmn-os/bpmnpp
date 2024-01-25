#include "SubProcess.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"
#include "UntypedStartEvent.h"

using namespace BPMN;

SubProcess::SubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent)
  : Node(subProcess)
  , FlowNode(subProcess,parent)
  , Activity(subProcess,parent)
  , Scope(subProcess)
  , startEvent(nullptr)
  , element(subProcess)
{
}

