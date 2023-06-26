#include "Model.h"
using namespace BPMN;
#include <iostream>
Model::Model(const std::string& filename)
{
  readBPMNFile(filename);
}

void Model::readBPMNFile(const std::string& filename)
{
std::cout << "Model: " << filename << std::endl;
  roots.push_back( std::unique_ptr<XML::XMLObject>(XML::XMLObject::createFromFile(filename)) );
  
  for ( XML::bpmn::tProcess& process : (*roots.rbegin())->getChildren<XML::bpmn::tProcess>() ) {
    processes.push_back(createRootNode(process));
  }
  
  for ( auto& node : processes ) {
    createChildNodes(node.get());
    createSequenceFlows(node.get());
    createReferences(node.get());
  }
}

std::unique_ptr<Node> Model::createRootNode(XML::bpmn::tProcess& process) {
  return std::make_unique<Node>(process);
}

std::unique_ptr<Node> Model::createChildNode(XML::bpmn::tFlowNode& flowNode, Node* parentNode) {
  return std::make_unique<Node>(flowNode,parentNode);
}

std::unique_ptr<SequenceFlow> Model::createSequenceFlow(XML::bpmn::tSequenceFlow& sequenceFlow, Node* scope) {
  return std::make_unique<SequenceFlow>(SequenceFlow(sequenceFlow,scope));
}

void Model::createChildNodes(Node* scope) {
  // add child nodes
  for (XML::bpmn::tFlowNode& flowNode: scope->get<>()->getChildren<XML::bpmn::tFlowNode>() ) {
    scope->childNodes.push_back(createChildNode(flowNode,scope));
  }
  for ( auto& childNode: scope->childNodes ) {
    createChildNodes(childNode.get());
  }
}

void Model::createSequenceFlows(Node* scope) {
  // add sequence flows within scope of the node
  for (XML::bpmn::tSequenceFlow& sequenceFlow: scope->get<>()->getChildren<XML::bpmn::tSequenceFlow>() ) {
    scope->sequenceFlows.push_back(createSequenceFlow(sequenceFlow,scope));
  }
  for ( auto& childNode: scope->childNodes ) {
    createSequenceFlows(childNode.get());
  }
}

void Model::createReferences(Node* scope) {
  if ( scope->parentNode ) {
    // link incoming sequence flows
    for ( auto& inflow : scope->get<XML::bpmn::tFlowNode>()->incoming ) {
      for (auto& sequenceFlow : scope->parentNode->sequenceFlows ) {
        if ( sequenceFlow->id.size() && inflow.get().textContent == sequenceFlow->id ) {
          scope->incoming.push_back(sequenceFlow.get());
          break;
        }
      }
    }
   
    // add to start nodes of parent if required 
    if ( scope->isStartNode() ) {
      scope->parentNode->startNodes.push_back(scope);
    }

    // link outgoing sequence flows
    for ( auto& outflow : scope->get<XML::bpmn::tFlowNode>()->outgoing ) {
      for (auto& sequenceFlow : scope->parentNode->sequenceFlows ) {
        if ( sequenceFlow->get()->id.has_value() && outflow.get().textContent == (std::string)sequenceFlow->get()->id->get() ) {
          scope->outgoing.push_back(sequenceFlow.get());
          break;
        }
      }
    }
  }

  for ( auto& childNode: scope->childNodes ) {
    createReferences(childNode.get());
  }
}

