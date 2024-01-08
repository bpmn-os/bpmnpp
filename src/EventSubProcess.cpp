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
  , startEvent(nullptr)
  , element(subProcess)
{
}
