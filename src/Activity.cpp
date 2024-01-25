#include "Activity.h"
#include "xml/bpmn/tLoopCharacteristics.h"
#include "xml/bpmn/tStandardLoopCharacteristics.h"
#include "xml/bpmn/tMultiInstanceLoopCharacteristics.h"

using namespace BPMN;

Activity::Activity(XML::bpmn::tActivity* activity, Scope* parent)
  : Node(activity)
  , FlowNode(activity,parent)
  , compensatedBy(nullptr)
  , isForCompensation(activity->isForCompensation.has_value() && activity->isForCompensation.value().get().value)
  , element(activity)
{
  auto marker = activity->getChildren<XML::bpmn::tLoopCharacteristics>();
  if ( !marker.empty() ) {
    if ( marker[0].get().is<XML::bpmn::tStandardLoopCharacteristics>() ) {
      loopCharacteristics = LoopCharacteristics::Loop;
    }
    else if ( auto multiInstanceMarker = marker[0].get().is<XML::bpmn::tMultiInstanceLoopCharacteristics>() ) {
      if ( multiInstanceMarker->isSequential.has_value() &&
        (bool)multiInstanceMarker->isSequential.value().get().value
      ) {
        loopCharacteristics = LoopCharacteristics::MultiInstanceSequential;
      }
      else {
        loopCharacteristics = LoopCharacteristics::MultiInstanceParallel;
      }
    }
    else {
      throw std::logic_error("Activity: Failed determining loop characteristics for activity '" + activity->id.value().get().value.value + "'");
    }
  }
}

