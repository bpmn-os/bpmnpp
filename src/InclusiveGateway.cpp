#include "InclusiveGateway.h"

using namespace BPMN;

InclusiveGateway::InclusiveGateway(XML::bpmn::tInclusiveGateway* inclusiveGateway, Scope* parent)
  : Gateway(inclusiveGateway,parent)
  , Node(inclusiveGateway)
  , element(inclusiveGateway)
{
}

