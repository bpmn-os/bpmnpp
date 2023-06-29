#include "Scope.h"
#include "FlowNode.h"

using namespace BPMN;

Scope::Scope(XML::bpmn::tBaseElement* element, Scope* parent)
  : Node(element,parent)
{
}

