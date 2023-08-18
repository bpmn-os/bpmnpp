#include "EventSubProcess.h"
#include "xml/bpmn/tStartEvent.h"
#include "xml/bpmn/tEventDefinition.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

EventSubProcess::EventSubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent)
  : Node(subProcess)
  , ChildNode(subProcess,parent)
  , Scope(subProcess)
  , element(subProcess)
{
  isInterrupting = true;
  isNonInterrupting = true;
  for ( auto startNode : startNodes ) {
    if ( auto startEvent = startNode->element->is<XML::bpmn::tStartEvent>(); startEvent ) { 
      if ( startEvent->getChildren<XML::bpmn::tEventDefinition>().empty() ) {
        throw std::runtime_error("EventSubProcess: no event definition provided for " + startNode->id);
      }
      if ( startEvent->isInterrupting ) {
        isNonInterrupting = false;
      }
      else {
        isInterrupting = false;
      }
    }
    else {
      throw std::runtime_error("EventSubProcess: implicit start provided for " + id);
    }
  }

}

