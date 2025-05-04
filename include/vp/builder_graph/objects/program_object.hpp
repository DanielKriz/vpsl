#ifndef VP_BUILDER_GRAPH_PROGRAM_OBJECT_HPP
#define VP_BUILDER_GRAPH_PROGRAM_OBJECT_HPP

#include <vp/builder_graph/objects/builder_object_interface.hpp>
#include <vp/types.hpp>

namespace vp {

class ProgramObject : public IBuilderGraphObject {
public:
    explicit ProgramObject(std::string name) : m_id(++m_programCounter), m_name(std::move(name)) { };
    ProgramObject() : m_id(++m_programCounter) { m_name = std::to_string(m_id); }

    [[nodiscard]] const std::string &getName() const noexcept {
        return m_name;
    }
private:
    inline static u64 m_programCounter { 0 };
    u64 m_id;
    std::string m_name;
};

} // namespace vp

#endif // VP_BUILDER_GRAPH_PROGRAM_OBJECT_HPP
