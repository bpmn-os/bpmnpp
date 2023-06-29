#ifndef BPMN_Gateway_H
#define BPMN_Gateway_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tGateway.h"
#include "FlowNode.h"

namespace BPMN {

class Gateway : public FlowNode {
  friend class Model;
public:
  Gateway(XML::bpmn::tGateway* gateway, Scope* parent);

  XML::bpmn::tGateway* element;
protected:
};

} // namespace BPMN

#endif // BPMN_Gateway_H
