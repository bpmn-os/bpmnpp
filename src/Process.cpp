#include "Process.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

Process::Process(XML::bpmn::tProcess* process)
  : Scope(process)
  , Node(process)
  , element(process)
{
}

