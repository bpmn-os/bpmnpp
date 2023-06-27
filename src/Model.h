#ifndef BPMN_Model_H
#define BPMN_Model_H

#include "Node.h"
#include "BoundaryEvent.h"
#include "SequenceFlow.h"
#include <memory>
#include <vector>
#include <string>

namespace BPMN {

class Node;
class SequenceFlow;

/**
 * @brief Represents a BPMN model with all its processes.
 *
 * The `Model` class encapsulates all processes with their nodes and sequence flows of a BPMN model.
 */
class Model {
protected:
	Model() {};
public:
	Model(const std::string& filename);
  virtual ~Model() = default;
  std::vector< std::unique_ptr<Node> > processes;
  std::vector<std::unique_ptr<XML::XMLObject> > roots;
protected:
  virtual void readBPMNFile(const std::string& filename);
  virtual std::unique_ptr<Node> createRootNode(XML::bpmn::tProcess& process);
  virtual std::unique_ptr<Node> createChildNode(XML::bpmn::tFlowNode& flowNode, Node* parentNode);
  virtual std::unique_ptr<Node> createBoundaryEvent(XML::bpmn::tBoundaryEvent& boundaryEvent, Node* parentNode);
  virtual std::unique_ptr<SequenceFlow> createSequenceFlow(XML::bpmn::tSequenceFlow& sequenceFlow, Node* scope);
  virtual void createChildNodes(Node* scope);
  virtual void createSequenceFlows(Node* scope);
  virtual void createReferences(Node* scope);
};

} // namespace BPMN

#endif // BPMN_Model_H
