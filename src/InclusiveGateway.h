#ifndef BPMN_InclusiveGateway_H
#define BPMN_InclusiveGateway_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tInclusiveGateway.h"
#include "Gateway.h"

namespace BPMN {

class InclusiveGateway : public Gateway {
  friend class Model;
public:
  InclusiveGateway(XML::bpmn::tInclusiveGateway* inclusiveGateway, Scope* parent);

  XML::bpmn::tInclusiveGateway* element;
protected:
};

} // namespace BPMN

#endif // BPMN_InclusiveGateway_H
