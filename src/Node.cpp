#include "Node.h"
#include "Scope.h"

using namespace BPMN;

Node::Node(XML::bpmn::tBaseElement* element)
  : BaseElement(element)
{
}

Node* Node::find(std::function<bool(Node*)> condition) {
  if (condition(this)) {
    return this;
  }

  if (Scope* scope = this->represents<Scope>(); scope) {
    for (auto& childNode : scope->childNodes) {
      Node* node = childNode.get();
      Node* result = node->find(condition);
      if (result != nullptr) {
        return result;
      }
    }
  }
  return nullptr;
}

const Node* Node::find(std::function<bool(const Node*)> condition) const {
  if (condition(this)) {
    return this;
  }

  if (const Scope* scope = this->represents<Scope>(); scope) {
    for (const auto& childNode : scope->childNodes) {
      const Node* node = childNode.get();
      const Node* result = node->find(condition);
      if (result != nullptr) {
        return result;
      }
    }
  }
  return nullptr;
}

std::vector< Node* > Node::find_all(std::function<bool(Node*)> condition) {
  std::vector< Node* > result;

  if (condition(this)) {
    result.push_back(this);
  }

  if ( Scope* scope = this->represents<Scope>(); scope ) {
    for ( auto &childNode : scope->childNodes) {
      Node* node = childNode.get();
      std::vector< Node* > childResults = node->find_all(condition);
      result.insert(result.end(), childResults.begin(), childResults.end());
    }
  }

  return result;
}

std::vector< const Node* > Node::find_all(std::function<bool(const Node*)> condition) const {
  std::vector< const Node* > result;

  if (condition(this)) {
    result.push_back(this);
  }

  if ( const Scope* scope = this->represents<Scope>(); scope ) {
    for ( const auto& childNode : scope->childNodes) {
      const Node* node = childNode.get();
      std::vector< const Node* > childResults = node->find_all(condition);
      result.insert(result.end(), childResults.begin(), childResults.end());
    }
  }

  return result;
}

