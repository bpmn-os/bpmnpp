#ifndef BPMN_EventSubProcess_H
#define BPMN_EventSubProcess_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tSubProcess.h"
#include "ChildNode.h"
#include "Scope.h"

namespace BPMN {

class EventSubProcess : public ChildNode, public Scope  {
  friend class Model;
public:
  EventSubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent);

  XML::bpmn::tSubProcess* element;
};

} // namespace BPMN

#endif // BPMN_EventSubProcess_H
