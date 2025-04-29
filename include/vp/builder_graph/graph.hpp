#ifndef VP_BUILDER_GRAPH_HPP
#define VP_BUILDER_GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <memory>

#include <vp/builder_graph/node.hpp>

namespace vp::build {


class BuilderGraph {
public:
    [[nodiscard]] INode &getRoot() const noexcept;
private:
    std::shared_ptr<INode> m_root;
};

} // namespace vp

#endif // VP_BUILDER_GRAPH_HPP
