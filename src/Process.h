#ifndef BPMN_Process_H
#define BPMN_Process_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tProcess.h"
#include "Scope.h"

namespace BPMN {

class Process : public Scope {
  friend class Model;
public:
  XML::bpmn::tProcess* element;
  Process(XML::bpmn::tProcess* process);
protected:
};

} // namespace BPMN

#endif // BPMN_Process_H
