#ifndef VP_BUILDER_GRAPH_HPP
#define VP_BUILDER_GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <memory>

#include <vp/builder_graph/node.hpp>
#include <vp/builder_graph/objects.hpp>
#include <vp/context.hpp>

namespace vp::build {

struct Graph {


ShaderObject m_globalShaderCode;
Context m_globalContext;

ProgramObject m_currentProgram;
ShaderObject m_currentShader;

std::vector<ProgramObject> m_programs;
std::vector<ShaderObject> m_shaders;
};

class BuilderGraph {
public:
    [[nodiscard]] INode &getRoot() const noexcept;
private:
    std::shared_ptr<INode> m_root;
};

} // namespace vp

#endif // VP_BUILDER_GRAPH_HPP
