#ifndef VP_BUILD_GRAPH_SHADER_BUILDER_HPP
#define VP_BUILD_GRAPH_SHADER_BUILDER_HPP

#include <string>
#include <vector>

#include <vp/builder_interface.hpp>
#include <vp/graphics/shader.hpp>

namespace vp {

class ShaderBuilder : public IBuilder {
public:
    ShaderBuilder() = default;
    virtual ~ShaderBuilder() = default;

    void build() const noexcept override;
    void reset() noexcept override;

    [[nodiscard]] ShaderBuilder &addLine(const std::string &line) noexcept;
    [[nodiscard]] ShaderBuilder &setName(const std::string &name) noexcept;
    [[nodiscard]] ShaderBuilder &setKind(gl::ShaderKind kind) noexcept;
    [[nodiscard]] ShaderBuilder &addToPreSet(gl::ShaderKind kind) noexcept;
    [[nodiscard]] ShaderBuilder &addToPostSet(gl::ShaderKind kind) noexcept;

    [[nodiscard]] gl::ShaderKind getKind() const noexcept;
    [[nodiscard]] const std::vector<std::string> &getSource() const noexcept;

private:
    std::vector<std::string> m_source;
    gl::ShaderKind m_kind;
};

} // namespace vp

#endif // VP_BUILD_GRAPH_wwwSHADER_BUILDER_HPP
