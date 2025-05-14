#ifndef VP_ENGINE_EXECUTION_NODE_HPP
#define VP_ENGINE_EXECUTION_NODE_HPP

#include <memory>

#include <vp/description/options.hpp>
#include <vp/graphics/opengl/program.hpp>

namespace vp {

class ExecutionNode {
public:
    ExecutionNode();
    [[nodiscard]] gl::opengl::Program &getProgram() noexcept { return *m_pProgram; }
    void applyContext() const noexcept;
    void setOptions(const Options &opts);
private:
    std::shared_ptr<gl::opengl::Program> m_pProgram;
    std::unique_ptr<Options> m_pOptions;
};

} // namespace vp

#endif // VP_ENGINE_EXECUTION_NODE_HPP
