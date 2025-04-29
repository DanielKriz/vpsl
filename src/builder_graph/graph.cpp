#include <vp/builder_graph/graph.hpp>

namespace vp::build {

INode &BuilderGraph::getRoot() const noexcept {
    return *m_root;
}

} // namespace vp
