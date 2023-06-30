#include "SubProcess.h"

using namespace BPMN;

SubProcess::SubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent)
  : Activity(subProcess,parent)
  , Scope(subProcess)
  , Node(subProcess)
  , element(subProcess)
{
}

