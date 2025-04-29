#ifndef VP_BUILDER_GRAPH_NODE_HPP
#define VP_BUILDER_GRAPH_NODE_HPP

namespace vp::build {

class INode {
public:
    void addLine();
    void addResource();
    void addToContext();
};

class Node : public INode {
};

};

#endif // VP_BUILDER_GRAPH_NODE_HPP
