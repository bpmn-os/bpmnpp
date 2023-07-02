#ifndef BPMN_EventSubProcess_H
#define BPMN_EventSubProcess_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tSubProcess.h"
#include "Scope.h"

namespace BPMN {

class EventSubProcess : public Scope {
  friend class Model;
public:
  EventSubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent);

  /// Reference to the parent node.
  Scope* parent;

  XML::bpmn::tSubProcess* element;

  /// An event subprocess is interrupting if all its start nodes are interrupting
  bool isInterrupting;
  /// An event subprocess is non-interrupting if all its start nodes are non-interrupting
  bool isNonInterrupting;

protected:
};

} // namespace BPMN

#endif // BPMN_EventSubProcess_H
