#ifndef BPMN_AdHocSubProcess_H
#define BPMN_AdHocSubProcess_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tAdHocSubProcess.h"
#include "SubProcess.h"

namespace BPMN {

class AdHocSubProcess : public SubProcess {
  friend class Model;
public:
  AdHocSubProcess(XML::bpmn::tAdHocSubProcess* adHocSubProcess, Scope* parent);

  XML::bpmn::tAdHocSubProcess* element;
protected:
};

} // namespace BPMN

#endif // BPMN_AdHocSubProcess_H
