#include "ExclusiveGateway.h"

using namespace BPMN;

ExclusiveGateway::ExclusiveGateway(XML::bpmn::tExclusiveGateway* exclusiveGateway, Scope* parent)
  : Node(exclusiveGateway)
  , Gateway(exclusiveGateway,parent)
  , element(exclusiveGateway)
{
}

