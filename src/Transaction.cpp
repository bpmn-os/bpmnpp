#include "Transaction.h"

using namespace BPMN;

Transaction::Transaction(XML::bpmn::tTransaction* transaction, Scope* parent)
  : SubProcess(transaction,parent)
  , Node(transaction,parent)
  , element(transaction)
{
}

