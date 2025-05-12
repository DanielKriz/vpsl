#include <vp/engine/execution_node.hpp>

namespace vp {

ExecutionNode::ExecutionNode() : m_pProgram(std::make_shared<gl::opengl::Program>()) {
}

} // namespace vp
