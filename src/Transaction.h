#ifndef BPMN_Transaction_H
#define BPMN_Transaction_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tTransaction.h"
#include "SubProcess.h"

namespace BPMN {

class Transaction : public SubProcess {
  friend class Model;
public:
  Transaction(XML::bpmn::tTransaction* transaction, Scope* parent);

  XML::bpmn::tTransaction* element;
protected:
};

} // namespace BPMN

#endif // BPMN_Transaction_H
