#ifndef VP_EXECUTION_SEQUENCE_NODE_HPP
#define VP_EXECUTION_SEQUENCE_NODE_HPP

namespace vp::gl { class Program; }

#include <memory>
#include <vector>

namespace vp {

class IResource;
class Context;

class ExecutionNode {
public:
    void execute() const;
    void bindResources() const;
    void switchContext() const;
    void useProgram() const;
private:
    std::shared_ptr<gl::Program> m_pProgram;
    std::vector<std::shared_ptr<IResource>> m_resources;
    std::shared_ptr<Context> m_pContext;
};

} // namespace vp

#endif // VP_EXECUTION_SEQUENCE_NODE_HPP
