#include "SubProcess.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"
#include "UntypedStartEvent.h"

using namespace BPMN;

SubProcess::SubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent)
  : Node(subProcess)
  , Activity(subProcess,parent)
  , Scope(subProcess)
  , element(subProcess)
{
  if ( startEvents.size() > 1 ) {
    throw std::runtime_error("SubProcess: more than one start node provided for " + id);
  }
  for ( auto startEvent : startEvents ) {
    if ( !startEvent->represents<UntypedStartEvent>() ) {
      throw std::runtime_error("SubProcess: event definition provided for " + startEvent->id);
    }
  }
}

