#include "SubProcess.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

SubProcess::SubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent)
  : Node(subProcess)
  , Activity(subProcess,parent)
  , Scope(subProcess)
  , element(subProcess)
{
  if ( startNodes.size() > 1 ) {
    throw std::runtime_error("SubProcess: more than one start node provided for " + id);
  }
  if ( startNodes.size()  && 
       startNodes[0]->element->getChildren<XML::bpmn::tEventDefinition>().size()
  ) {
    throw std::runtime_error("SubProcess: event definition provided for " + startNodes[0]->id);
  }
}

