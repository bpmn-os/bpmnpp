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

class Activity : virtual public FlowNode {
  friend class Model;
public:
  Activity(XML::bpmn::tActivity* activity, Scope* parent);

  std::vector< BoundaryEvent* > boundaryEvents;
  Node* compensatedBy; ///< Pointer to compensation activity or compensation event sub-process
  bool isForCompensation;
  enum class LoopCharacteristics { MultiInstanceParallel, MultiInstanceSequential, Loop };
  std::optional<LoopCharacteristics> loopCharacteristics;

  XML::bpmn::tActivity* element;
};

} // namespace BPMN

#endif // BPMN_Activity_H
