#include "EventSubProcess.h"
#include "xml/bpmn/tStartEvent.h"
#include "xml/bpmn/tEventDefinition.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"
#include "TypedStartEvent.h"

using namespace BPMN;

EventSubProcess::EventSubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent)
  : Node(subProcess)
  , ChildNode(subProcess,parent)
  , Scope(subProcess)
  , element(subProcess)
{
  if ( startEvents.size() > 1 ) {
    throw std::runtime_error("EventSubProcess: more than one start node provided for " + id);
  }
  for ( auto startEvent : startEvents ) {
    if ( !startEvent->represents<TypedStartEvent>() ) {
      throw std::runtime_error("EventSubProcess: no event definition provided for " + startEvent->id);
    }
  }
}
