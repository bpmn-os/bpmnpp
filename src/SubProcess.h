#ifndef BPMN_SubProcess_H
#define BPMN_SubProcess_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tSubProcess.h"
#include "Activity.h"
#include "Scope.h"

namespace BPMN {

class UntypedStartEvent;

class SubProcess : public Activity, public Scope {
  friend class Model;
public:
  SubProcess(XML::bpmn::tSubProcess* subProcess, Scope* parent);
  UntypedStartEvent* startEvent;
  XML::bpmn::tSubProcess* element;
protected:
};

} // namespace BPMN

#endif // BPMN_SubProcess_H
