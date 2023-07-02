#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

Scope::Scope(XML::bpmn::tBaseElement* element)
  : Node(element)
{
}

