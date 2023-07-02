#include "Transaction.h"
#include "Scope.h"
#include "FlowNode.h"
#include "EventSubProcess.h"
#include "SequenceFlow.h"

using namespace BPMN;

Transaction::Transaction(XML::bpmn::tTransaction* transaction, Scope* parent)
  : SubProcess(transaction,parent)
  , Node(transaction)
  , element(transaction)
{
}

