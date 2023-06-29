#ifndef BPMN_ExclusiveGateway_H
#define BPMN_ExclusiveGateway_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tExclusiveGateway.h"
#include "Gateway.h"

namespace BPMN {

class ExclusiveGateway : public Gateway {
  friend class Model;
public:
  ExclusiveGateway(XML::bpmn::tExclusiveGateway* exclusiveGateway, Scope* parent);

  XML::bpmn::tExclusiveGateway* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ExclusiveGateway_H
