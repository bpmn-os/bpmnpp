#include "SubProcess.h"

using namespace BPMN;

SubProcess::SubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent)
  : Activity(subProcess,parent)
  , Scope(subProcess,parent)
  , Node(subProcess,parent)
  , element(subProcess)
{
}

