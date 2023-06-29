#ifndef BPMN_Scope_H
#define BPMN_Scope_H

#include <memory>
#include <vector>
#include <optional>
#include "Node.h"
#include "FlowNode.h"
#include "SequenceFlow.h"

namespace BPMN {

class Scope : virtual public Node {
  friend class Model;
public:
  Scope(XML::bpmn::tBaseElement* element, Scope* parent = nullptr);

  /// Vector containing all flow nodes within the scope of the nodes.
  std::vector< std::unique_ptr<FlowNode> > childNodes;

  /// Vector containing all flow nodes that may start execution of the scope.
  std::vector< FlowNode* > startNodes;

  /// Vector containing all sequence flows within the scope.
  std::vector< std::unique_ptr<SequenceFlow> > sequenceFlows;

protected:
};

} // namespace BPMN

#endif // BPMN_Scope_H
