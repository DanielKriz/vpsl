#ifndef VP_GRAPHICS_OPENGL_SHADER_HPP
#define VP_GRAPHICS_OPENGL_SHADER_HPP

#include <memory>
#include <string>

#include <fmt/core.h>
#include <glad/glad.h>
#include <glslang/Public/ResourceLimits.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/SPIRV/GlslangToSpv.h>

#include <vp/description/shader_code.hpp>
#include <vp/graphics/opengl/object.hpp>
#include <vp/graphics/opengl/utils.hpp>
#include <vp/types.hpp>

namespace vp::gl::opengl {

/// @brief Scoped enum for different kinds of shaders in OpenGL.
enum class ShaderKind : enum32 {
    Fragment = GL_FRAGMENT_SHADER,
    Vertex = GL_VERTEX_SHADER,
    TesselationControl = GL_TESS_CONTROL_SHADER,
    TesselationEvaluation = GL_TESS_EVALUATION_SHADER,
    Geometry = GL_GEOMETRY_SHADER,
    Compute = GL_COMPUTE_SHADER,
};

/// @brief Scoped enum for different language kinds that are supported by glslang
enum class ShaderLanguageKind : enum32 {
    Glsl,
    Hlsl,
};

/// @brief Wrapper around shader object.
/// It automatically destroys a shader object held by opengl runtime if it is not held anywhere.
class Shader {
private:
    /// @brief Default constructor that initializes the descriptor.
    /// It shall be called by all other constructors and it cannot be called by the consumer of
    /// the API.
    explicit Shader(ShaderKind kind);

public:
    /// @brief Constructor that is using the internal opengl shader compiler.
    /// It does not support any other langauge, but GLSL. This is due to the fact that it is not
    /// using SPIR-V internally.
    Shader(ShaderKind kind, const std::string &source);


    /// @brief Constructor that is using the glslang compiler.
    Shader(ShaderKind kind, const std::string &source, ShaderLanguageKind langKind);

    /// @brief Getter for the descriptor of the this shader object.
    /// @returns Copy of descriptor of this shader object.
    [[nodiscard]] u32 getDescriptor() const noexcept;

    /// @brief Static method for creation of Shader objects from shader code.
    /// @param code Shader code that should be already composed.
    static Shader initFromShaderCode(const ShaderCode &code);
private:
    /// @brief Shared pointer for the descriptor, that makes it possible to simply move this whole
    /// object around.
    std::shared_ptr<u32> m_pDescriptor;
};

} // namespace vp::gl::opengl

#endif // VP_GRAPHICS_OPENGL_SHADER_HPP
