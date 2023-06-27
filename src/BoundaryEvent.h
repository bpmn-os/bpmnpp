#ifndef BPMN_BoundaryEvent_H
#define BPMN_BoundaryEvent_H

#include "xml/bpmn/tBoundaryEvent.h"
#include "Node.h"

namespace BPMN {

/**
 * @brief Represents a boundary event attached to an activity in a BPMN process.
 */
class BoundaryEvent : public Node {
  friend class Model;
public:
  BoundaryEvent(XML::bpmn::tBoundaryEvent& boundaryEvent, Node* parentNode);
  Node& attachedTo;
protected:
  Node& resolveReference();
};

} // namespace BPMN

#endif // BPMN_BoundaryEvent_H
