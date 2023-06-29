#ifndef BPMN_ComplexGateway_H
#define BPMN_ComplexGateway_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tComplexGateway.h"
#include "Gateway.h"

namespace BPMN {

class ComplexGateway : public Gateway {
  friend class Model;
public:
  ComplexGateway(XML::bpmn::tComplexGateway* complexGateway, Scope* parent);

  XML::bpmn::tComplexGateway* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ComplexGateway_H
