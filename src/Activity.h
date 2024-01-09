#ifndef BPMN_Activity_H
#define BPMN_Activity_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tActivity.h"
#include "FlowNode.h"
#include "BoundaryEvent.h"

namespace BPMN {

class BoundaryEvent;

class Activity : public FlowNode {
  friend class Model;
public:
  Activity(XML::bpmn::tActivity* activity, Scope* parent);

  std::vector< BoundaryEvent* > boundaryEvents;
  Node* compensatedBy; ///< Pointer to compensation activity or compensation event sub-process
  bool isForCompensation;
  XML::bpmn::tActivity* element;
protected:
};

} // namespace BPMN

#endif // BPMN_Activity_H
