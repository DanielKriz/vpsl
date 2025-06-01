#include <vp/description/shader_code.hpp>
#include <vp/graphics/opengl/shader.hpp>

#include <stdexcept>

#include <spdlog/spdlog.h>

namespace vp::gl::opengl {

std::ostream &operator<<(std::ostream &os, const ShaderKind kind) {
    std::string_view shaderRepr = [&kind]() {
        using enum ShaderKind;
        switch (kind) {
        case Fragment: return "Fragment";
        case Vertex: return "Vertex";
        case TesselationControl: return "Tessellation Control";
        case TesselationEvaluation: return "Tessellation Evaluation";
        case Geometry: return "Geometry";
        case Compute: return "Compute";
        default:
            throw std::runtime_error("Unknown Shader Kind for representation");
        }
    }();
    return os << shaderRepr;
}

Shader::Shader(ShaderKind kind) {
    const auto desc = glCreateShader(enum_cast<ShaderKind>(kind));
    m_pDescriptor = std::shared_ptr<u32>(new u32(desc), [](const u32 *pDesc){
            glDeleteShader(*pDesc);
            delete pDesc;
    });
}

u32 Shader::getDescriptor() const noexcept {
    return *m_pDescriptor;
}

Shader::Shader(ShaderKind kind, const std::string &source) : Shader(kind) {
    const auto *p_source = source.c_str();
    glShaderSource(getDescriptor(), 1, &p_source, nullptr);
    int isCompilationSuccess = 0;
    glCompileShader(getDescriptor());
    glGetShaderiv(getDescriptor(), GL_COMPILE_STATUS, &isCompilationSuccess);
    if (not static_cast<bool>(isCompilationSuccess)) {
        auto msg = utils::getShaderErrorMessage(getDescriptor());
        throw std::runtime_error(
            fmt::format("Shader compilation was not successful: ({})", msg)
        );
    }
}

Shader::Shader(
    ShaderKind kind,
    const std::string &source,
    [[maybe_unused]] ShaderLanguageKind langKind
) : Shader(kind) {
    glslang::InitializeProcess();
    const EShLanguage stage = [kind]() {
        using enum ShaderKind;
        switch (kind) {
        case Vertex:
            return EShLangVertex;
        case Fragment:
            return EShLangFragment;
        case Geometry:
            return EShLangGeometry;
        case TesselationControl:
            return EShLangTessControl;
        case TesselationEvaluation:
            return EShLangTessEvaluation;
        case Compute:
            return EShLangCompute;
        default:
            throw std::runtime_error("Unknown shader type found");
        }
    }();
    glslang::TShader shader(stage);
    const char *pSource = source.c_str();
    shader.setStrings(&pSource, 1);
    shader.setEnvInput(glslang::EShSourceGlsl, stage, glslang::EShClientOpenGL, 450);
    shader.setEnvClient(glslang::EShClientOpenGL, glslang::EShTargetOpenGL_450);
    shader.setEnvTarget(glslang::EshTargetSpv, glslang::EShTargetSpv_1_1);

    auto isSuccess = shader.parse(GetDefaultResources(), 450, false, EShMsgDefault);

    if (not isSuccess) {
        spdlog::error("Cannot create shader due to syntax error");
        throw std::runtime_error(shader.getInfoLog());
    }

    glslang::TProgram program;
    program.addShader(&shader);
    program.link(EShMsgDefault);
    glslang::TIntermediate *intermediate = program.getIntermediate(stage);

    std::vector<u32> SPIRVBinary;
    glslang::GlslangToSpv(*intermediate, SPIRVBinary);
    glslang::FinalizeProcess();
    const auto size = static_cast<i32>(SPIRVBinary.size() * (sizeof(u32) / sizeof(u8)));
    glslang::OutputSpvBin(SPIRVBinary, "output.bin");

    glShaderBinary(1, m_pDescriptor.get(), GL_SHADER_BINARY_FORMAT_SPIR_V, SPIRVBinary.data(), size);
    glSpecializeShader(getDescriptor(), "main", 0, nullptr, nullptr);

    int isCompilationSuccess = 0;
    glGetShaderiv(getDescriptor(), GL_COMPILE_STATUS, &isCompilationSuccess);
    if (not static_cast<bool>(isCompilationSuccess)) {
        auto msg = utils::getShaderErrorMessage(getDescriptor());
        throw std::runtime_error(
            fmt::format("Shader compilation was no successful: ({})", msg)
        );
    }
}

Shader Shader::initFromShaderCode(const ShaderCode &code) {
    const ShaderKind kind = [&code]() {
        using enum ShaderCodeKind;
        switch (code.getKind()) {
        case Fragment: return ShaderKind::Fragment;
        case Vertex: return ShaderKind::Vertex;
        case TesselationEvaluation: return ShaderKind::TesselationEvaluation;
        case TesselationControl: return ShaderKind::TesselationControl;
        case Geometry: return ShaderKind::Geometry;
        case Compute: return ShaderKind::Compute;
        default:
            throw std::runtime_error("Unknown shader type");
        }
    }();

    return { kind, code.createSource(), ShaderLanguageKind::Glsl };
}

} // namespace vp::gl::opengl
