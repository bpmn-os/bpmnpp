#include "MessageFlow.h"
#include "Model.h"
#include "Process.h"
#include "Scope.h"
#include "FlowNode.h"

using namespace BPMN;

MessageFlow::MessageFlow(XML::bpmn::tMessageFlow* messageFlow)
  : BaseElement(messageFlow)
  , element(messageFlow)
  , source( {nullptr,nullptr} )
  , target( {nullptr,nullptr} )
{
}

void MessageFlow::initialize(std::vector< std::unique_ptr<Process> >& processes, std::unordered_map<std::string,std::string>& participantMap) {
  // find source
  if ( participantMap.contains(element->sourceRef.value.value) ) {
    // source is provided by participant reference
    for (auto& process : processes ) {
      if ( process->id == participantMap[element->sourceRef.value.value] ) {
        source = { process.get(), nullptr };
        break;
      }
      FlowNode* flowNode = findRecursive(element->sourceRef.value.value, process->as<Scope>());
      if ( flowNode ) {
        source = { process.get(), flowNode };
        break;
      }
    }
    if ( !source.first ) {
      throw std::runtime_error("MessageFlow: cannot find source of '" + id +"'");
    }
  }
  else {
    // source is provided by node reference (or empty collapsed participant)
    for (auto& process : processes ) {
      FlowNode* flowNode = findRecursive(element->sourceRef.value.value, process->as<Scope>());
      if ( flowNode ) {
        source = { process.get(), flowNode };
        break;
      }
    }
  }

  // find target
  if ( participantMap.contains(element->targetRef.value.value) ) {
    for (auto& process : processes ) {
      if ( process->id == participantMap[element->targetRef.value.value] ) {
        target = { process.get(), nullptr };
        break;
      }
      FlowNode* flowNode = findRecursive(element->targetRef.value.value, process->as<Scope>());
      if ( flowNode ) {
        target = { process.get(), flowNode };
        break;
      }

    }
    if ( !target.first ) {
      throw std::runtime_error("MessageFlow: cannot find target of '" + id +"'");
    }
  }
  else {
    // target is provided by node reference (or empty collapsed participant)
    for (auto& process : processes ) {
      FlowNode* flowNode = findRecursive(element->targetRef.value.value, process->as<Scope>());
      if ( flowNode ) {
        target = { process.get(), flowNode };
        break;
      }
    }
  }
}

FlowNode* MessageFlow::findRecursive(std::string& id, Scope* scope) {
  for ( auto& childNode : scope->childNodes ) {
    if ( childNode->get<>()->id.has_value() && id == childNode->get<>()->id->get().value.value ) {
      return childNode->as<FlowNode>();
    }
    if ( auto childScope = childNode->represents<Scope>(); childScope ) {
      FlowNode* flowNode = findRecursive(id, childScope);
      if ( flowNode ) {
        return flowNode;
      }
    }
  }
  return nullptr;
}

