#include "Process.h"
#include "FlowNode.h"

using namespace BPMN;

Process::Process(XML::bpmn::tProcess* process)
  : Scope(process)
  , Node(process)
  , element(process)
{
}

