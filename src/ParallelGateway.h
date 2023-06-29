#ifndef BPMN_ParallelGateway_H
#define BPMN_ParallelGateway_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tParallelGateway.h"
#include "Gateway.h"

namespace BPMN {

class ParallelGateway : public Gateway {
  friend class Model;
public:
  ParallelGateway(XML::bpmn::tParallelGateway* parallelGateway, Scope* parent);

  XML::bpmn::tParallelGateway* element;
protected:
};

} // namespace BPMN

#endif // BPMN_ParallelGateway_H
