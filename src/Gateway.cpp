#include "Gateway.h"

using namespace BPMN;

Gateway::Gateway(XML::bpmn::tGateway* gateway, Scope* parent)
  : Node(gateway)
  , FlowNode(gateway,parent)
  , element(gateway)
{
}

