#include <vp/description/shader_builder.hpp>

namespace vp::desc {

ShaderBuilder &ShaderBuilder::addLine(const std::string &line) noexcept {
    return *this;
}

ShaderCodeKind ShaderBuilder::getKind() const noexcept {
    return m_kind;
}

const std::vector<std::string> &ShaderBuilder::getSource() const noexcept {
    return m_source;
}

} // namespace vp::desc
