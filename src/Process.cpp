#include "Process.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

Process::Process(XML::bpmn::tProcess* process)
  : Node(process)
  , Scope(process)
  , element(process)
{
}

