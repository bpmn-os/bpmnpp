#ifndef BPMN_CallActivity_H
#define BPMN_CallActivity_H

#include <memory>
#include <vector>
#include <optional>
#include "xml/bpmn/tCallActivity.h"
#include "Activity.h"

namespace BPMN {

class CallActivity : public Activity {
  friend class Model;
public:
  CallActivity(XML::bpmn::tCallActivity* callActivity, Scope* parent);

  XML::bpmn::tCallActivity* element;
protected:
};

} // namespace BPMN

#endif // BPMN_CallActivity_H
