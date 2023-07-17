#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

Scope::Scope(XML::bpmn::tBaseElement* element)
  : Node(element)
{
}

void Scope::add(std::unique_ptr<Node> node) {
  childNodes.push_back(std::move(node));
  auto childNode = childNodes.end() - 1;
  if ( auto flowNode = childNode->get()->represents<FlowNode>(); flowNode ) {
    flowNodes.push_back(flowNode);
  }
  else if ( auto eventSubProcess = childNode->get()->represents<EventSubProcess>(); eventSubProcess ) {
    eventSubProcesses.push_back(eventSubProcess);
  }
  else {
    throw std::logic_error("Scope: illegal child node '" + childNode->get()->id + "'");
  }
}

void Scope::add(std::unique_ptr<SequenceFlow> sequenceFlow) {
  sequenceFlows.push_back(std::move(sequenceFlow));
}

