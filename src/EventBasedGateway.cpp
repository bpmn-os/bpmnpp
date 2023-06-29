#include "EventBasedGateway.h"

using namespace BPMN;

EventBasedGateway::EventBasedGateway(XML::bpmn::tEventBasedGateway* eventBasedGateway, Scope* parent)
  : Gateway(eventBasedGateway,parent)
  , Node(eventBasedGateway,parent)
  , element(eventBasedGateway)
{
}

