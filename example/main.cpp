#include <iostream>
#include <sstream>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <bpmn++.h>

using namespace std;
using namespace BPMN;
//namespace xml = XML::bpmn; // use alias to shorten declarations

class ResourceAwareNode : public Node {
public:
	ResourceAwareNode(XML::bpmn::tProcess& process) : Node(process) { x = 42; };
  ResourceAwareNode(XML::bpmn::tFlowNode& flowNode, Node* parentNode) : Node(flowNode,parentNode) { x = 23;};
  int x;
};

class ResourceAwareSequenceFlow : public SequenceFlow {
public:
	ResourceAwareSequenceFlow(XML::bpmn::tSequenceFlow& sequenceFlow, Node* scope) : SequenceFlow(sequenceFlow,scope) { y = 317; };
  int y;
};

class ResourceAwareModel : public Model {
public:
	ResourceAwareModel(const std::string& filename)  { Model::readBPMNFile(filename); };
  std::unique_ptr<Node> createRootNode(XML::bpmn::tProcess& process) override {
//cout << "ResourceAwareModel:createRootNode" << endl;
    return std::make_unique<ResourceAwareNode>(process);
  };
  std::unique_ptr<Node> createChildNode(XML::bpmn::tFlowNode& flowNode, Node* parentNode) override {
//cout << "ResourceAwareModel:createChildNode" << endl;
    return std::make_unique<ResourceAwareNode>(flowNode,parentNode);
  };
  std::unique_ptr<SequenceFlow> createSequenceFlow(XML::bpmn::tSequenceFlow& sequenceFlow, Node* scope) override {
//cout << "ResourceAwareModel:createSequenceFlow" << endl;
    return std::make_unique<ResourceAwareSequenceFlow>(sequenceFlow,scope);
  };
};


int main(int argc, char **argv) {
  if ( argc != 2 ) {
    cout << "Usage: " << argv[0] << " <bpmn-file>" << endl;
    return 0;
  }

//  Model model(argv[1]);
  ResourceAwareModel model(argv[1]);

  cout << "Number of processes: " << model.processes.size() << endl;
  for ( auto& processNode : model.processes ) {
//    if ( processNode->represents<ResourceAwareNode>() ) cout << "ResourceAwareNode" << endl;
//    cout << processNode->as<ResourceAwareNode>()->x << endl;

    XML::bpmn::tProcess& process = *processNode->get<XML::bpmn::tProcess>();

    cout << "- Process";
    if ( process.id.has_value() ) {
      cout << " with id '" << (string)process.id->get() << "'";
    }
    else {
      cout << " without id";
    }
    if ( process.isExecutable.has_value() && process.isExecutable->get() ) {
      cout << " is executable and"; 
    }

    cout << " has " << processNode->childNodes.size() << " child node(s)";  
    cout << " and " << processNode->sequenceFlows.size() << " sequence flow(s) and starts with:";
    for ( auto& startNode : processNode->startNodes ) {
      cout << " " << startNode->id;
    }
    cout << "." << endl;

    for ( auto& childNode : processNode->childNodes ) {
//    cout << childNode->as<ResourceAwareNode>()->x << endl;
      cout << "  - " << childNode->get<>()->className;
      if ( childNode->id.size() ) {
        cout << " with id '" << (string)childNode->id << "'";
      }
      else {
        cout << " without id";
      }
      cout << " has " << childNode->childNodes.size() << " child node(s)";  
      cout << ", " << childNode->incoming.size() << " incoming and " << childNode->outgoing.size() << " outgoing arc(s)." << endl;
      for ( auto& incoming : childNode->incoming ) {
//        cout << incoming->as<ResourceAwareSequenceFlow>()->y << endl;
        cout << "    - from node " << (std::string)incoming->source->id << endl;
      }
      for ( auto& outgoing : childNode->outgoing ) {
//        cout << outgoing->as<ResourceAwareSequenceFlow>()->y << endl;
        cout << "    - to node " << (std::string)outgoing->target->id << endl;
      }
    }
  }
  return 0;
}

