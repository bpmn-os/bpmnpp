#include "ParallelGateway.h"

using namespace BPMN;

ParallelGateway::ParallelGateway(XML::bpmn::tParallelGateway* parallelGateway, Scope* parent)
  : Gateway(parallelGateway,parent)
  , Node(parallelGateway,parent)
  , element(parallelGateway)
{
}

