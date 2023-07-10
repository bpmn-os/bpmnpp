#include "ParallelGateway.h"

using namespace BPMN;

ParallelGateway::ParallelGateway(XML::bpmn::tParallelGateway* parallelGateway, Scope* parent)
  : Node(parallelGateway)
  , Gateway(parallelGateway,parent)
  , element(parallelGateway)
{
}

