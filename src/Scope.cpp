#include "Scope.h"
#include "FlowNode.h"
#include "Activity.h"
#include "CompensateBoundaryEvent.h"
#include "CompensateStartEvent.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

Scope::Scope(XML::bpmn::tBaseElement* element)
  : Node(element)
  , compensationEventSubProcess(nullptr)
{
}

void Scope::add(std::unique_ptr<Node> node) {
  childNodes.push_back(std::move(node));
  auto childNode = childNodes.end() - 1;
  if ( auto flowNode = childNode->get()->represents<FlowNode>(); flowNode ) {
    if ( flowNode->represents<CompensateBoundaryEvent>() ) {
      // nothing to be done for CompensateBoundaryEvent
    }
    else if ( auto activity = flowNode->represents<Activity>();
      activity && 
      activity->element->isForCompensation.has_value() && 
      (bool)activity->element->isForCompensation.value().get().value
    ) {
      compensationActivities.push_back(activity);
    }
    else {
      flowNodes.push_back(flowNode);
    }
  }
  else if ( auto eventSubProcess = childNode->get()->represents<EventSubProcess>(); eventSubProcess ) {
    if ( eventSubProcess->startEvents.size() == 1 && 
      eventSubProcess->startEvents.front()->represents<CompensateStartEvent>()
    ) {
      if ( !compensationEventSubProcess ) {
        throw std::runtime_error("Scope: multiple compensation event subprocess for scope '" + id + "'");
      }
      compensationEventSubProcess = eventSubProcess;
      if ( auto activity =  this->as<Activity>(); activity ) {
        activity->compensatedBy = compensationEventSubProcess;
      }
      else {
        throw std::runtime_error("Scope: compensation event subprocess provided for non-activity '" + id + "'");
      }
    }
    else {
      eventSubProcesses.push_back(eventSubProcess);
    }
  }
  else {
    throw std::logic_error("Scope: illegal child node '" + childNode->get()->id + "'");
  }
}

void Scope::add(std::unique_ptr<SequenceFlow> sequenceFlow) {
  sequenceFlows.push_back(std::move(sequenceFlow));
}

