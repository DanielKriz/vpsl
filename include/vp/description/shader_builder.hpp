#ifndef VP_DESCRIPTION_SHADER_BUILDER_HPP
#define VP_DESCRIPTION_SHADER_BUILDER_HPP

#include <string>
#include <vector>

#include <vp/description/shader_code.hpp>

namespace vp::desc {

class ShaderBuilder final {
public:
    [[nodiscard]] ShaderBuilder &addLine(const std::string &line) noexcept;
    [[nodiscard]] ShaderBuilder &setName(const std::string &name) noexcept;
    [[nodiscard]] ShaderBuilder &setKind(ShaderCodeKind kind) noexcept;
    [[nodiscard]] ShaderBuilder &addToPreSet(ShaderCodeKind kind) noexcept;
    [[nodiscard]] ShaderBuilder &addToPostSet(ShaderCodeKind kind) noexcept;

    [[nodiscard]] ShaderCodeKind getKind() const noexcept;
    [[nodiscard]] const std::vector<std::string> &getSource() const noexcept;

private:
    std::vector<std::string> m_source;
    ShaderCodeKind m_kind;
};

} // namespace vp::desc

#endif // VP_DESCRIPTION_SHADER_BUILDER_HPP
