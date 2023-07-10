#include "ComplexGateway.h"

using namespace BPMN;

ComplexGateway::ComplexGateway(XML::bpmn::tComplexGateway* complexGateway, Scope* parent)
  : Node(complexGateway)
  , Gateway(complexGateway,parent)
  , element(complexGateway)
{
}

