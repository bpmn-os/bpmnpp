#include "ExclusiveGateway.h"

using namespace BPMN;

ExclusiveGateway::ExclusiveGateway(XML::bpmn::tExclusiveGateway* exclusiveGateway, Scope* parent)
  : Gateway(exclusiveGateway,parent)
  , Node(exclusiveGateway,parent)
  , element(exclusiveGateway)
{
}

