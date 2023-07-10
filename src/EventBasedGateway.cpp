#include "EventBasedGateway.h"

using namespace BPMN;

EventBasedGateway::EventBasedGateway(XML::bpmn::tEventBasedGateway* eventBasedGateway, Scope* parent)
  : Node(eventBasedGateway)
  , Gateway(eventBasedGateway,parent)
  , element(eventBasedGateway)
{
}

