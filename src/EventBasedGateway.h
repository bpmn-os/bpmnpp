#ifndef BPMN_EventBasedGateway_H
#define BPMN_EventBasedGateway_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tEventBasedGateway.h"
#include "Gateway.h"

namespace BPMN {

class EventBasedGateway : public Gateway {
  friend class Model;
public:
  EventBasedGateway(XML::bpmn::tEventBasedGateway* eventBasedGateway, Scope* parent);

  XML::bpmn::tEventBasedGateway* element;
protected:
};

} // namespace BPMN

#endif // BPMN_EventBasedGateway_H
