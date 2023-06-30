#include "ComplexGateway.h"

using namespace BPMN;

ComplexGateway::ComplexGateway(XML::bpmn::tComplexGateway* complexGateway, Scope* parent)
  : Gateway(complexGateway,parent)
  , Node(complexGateway)
  , element(complexGateway)
{
}

