#include "InclusiveGateway.h"

using namespace BPMN;

InclusiveGateway::InclusiveGateway(XML::bpmn::tInclusiveGateway* inclusiveGateway, Scope* parent)
  : Node(inclusiveGateway)
  , Gateway(inclusiveGateway,parent)
  , element(inclusiveGateway)
  , defaultFlow(nullptr)
{
}

