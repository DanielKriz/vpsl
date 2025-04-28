#include <vp/builder_graph/shader_builder.hpp>

namespace vp {
void ShaderBuilder::build() const noexcept {

}

void ShaderBuilder::reset() noexcept {

}

ShaderBuilder &ShaderBuilder::addLine(const std::string &line) noexcept {
    return *this;
}

gl::ShaderKind ShaderBuilder::getKind() const noexcept {
    return m_kind;
}

const std::vector<std::string> &ShaderBuilder::getSource() const noexcept {
    return m_source;
}

} // namespace vp
