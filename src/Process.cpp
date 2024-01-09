#include "Process.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

Process::Process(XML::bpmn::tProcess* process)
  : Node(process)
  , Scope(process)
  , isExecutable(process->isExecutable.has_value() && process->isExecutable.value().get().value)
  , element(process)
{
}

