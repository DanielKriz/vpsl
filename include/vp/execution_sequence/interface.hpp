#ifndef VP_EXECUTION_SEQUENCE_INTERFACE_HPP
#define VP_EXECUTION_SEQUENCE_INTERFACE_HPP

#include <vector>

#include <vp/execution_sequence/node.hpp>

namespace vp {

class ExecutionSequence {
public:
    void execute() const;
    void addNode(ExecutionNode &&node) noexcept;
    void sortNodes() noexcept;
private:
    std::vector<ExecutionNode> m_nodes;
};

} // namespace vp

#endif // VP_EXECUTION_SEQUENCE_INTERFACE_HPP
