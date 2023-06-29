#include "Gateway.h"

using namespace BPMN;

Gateway::Gateway(XML::bpmn::tGateway* gateway, Scope* parent)
  : FlowNode(gateway,parent)
  , Node(gateway,parent)
  , element(gateway)
{
}

