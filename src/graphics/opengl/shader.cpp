#include "vp/description/shader_code.hpp"
#include <vp/graphics/opengl/shader.hpp>

namespace vp::gl::opengl {

#if 0
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
        }
    }();
    return os << shaderRepr;
}
#endif

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

Shader::Shader(ShaderKind kind, const std::string &source, ShaderLanguageKind langKind)
    : Shader(kind) {
#if 1
    glslang::InitializeProcess();
    const EShLanguage stage = [kind]() {
        using enum ShaderKind;
        switch (kind) {
        case Vertex:
            return EShLangVertex;
        case Fragment:
            return EShLangFragment;
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

    shader.parse(GetDefaultResources(), 450, false, EShMsgDefault);

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

    GLint maxLength = 0;
    glGetShaderiv(getDescriptor(), GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(getDescriptor(), maxLength, &maxLength, &infoLog[0]);
    std::string infoLogStr{infoLog.begin(), infoLog.end()};
#else
    fmt::println("Source Code to compile:\n{}", source);

    m_descriptor = glCreateShader(enum_cast<ShaderKind>(kind));

    glslang::InitializeProcess();
    fmt::println("glslang GLSL version: {}", glslang::GetGlslVersionString());
    const EShLanguage stage = [kind]() {
        using enum ShaderKind;
        switch (kind) {
        case Vertex:
            return EShLangVertex;
        case Fragment:
            return EShLangFragment;
        default:
            throw std::runtime_error("Unknown shader type found");
        }
    }();
    glslang::TShader shader(stage);
    std::cout << 1 << std::endl;
    const char *pSource = source.c_str();
    shader.setStrings(&pSource, 1);
#if 1
    shader.setEnvInput(glslang::EShSourceGlsl, stage, glslang::EShClientOpenGL, 450);
#else
    // Currently this would not work, because it is only possible to transpile HLSL
    // to vulkan-compatible SPIR-V, which is not currently working with OpenGL.
    // Because of that there has to be additionale step where we have to transpile the
    // vulkan compatible SPIR-V to GLSL and then again to SPIR-V...
    shader.setEnvInput(glslang::EShSourceHlsl, stage, glslang::EShClientOpenGL, 450);
#endif
    shader.setEnvClient(glslang::EShClientOpenGL, glslang::EShTargetOpenGL_450);
    shader.setEnvTarget(glslang::EshTargetSpv, glslang::EShTargetSpv_1_1);
    // shader.setEnvTarget(glslang::EShTargetOpenGL, glslang::EShTargetSpv_1_6);

    // TBuiltInResource resource{};

    // std::cout << GetDefaultTBuiltInResourceString() << std::endl;

    std::cout << 2 << std::endl;
    std::string versionStr;
    glslang::GetSpirvVersion(versionStr);
    fmt::println("SPIR-V Version: {} | {}", versionStr, glslang::GetSpirvGeneratorVersion());

    shader.parse(
        GetDefaultResources(),
        // &resource,
        450,
        false,
        EShMsgDefault
    );

    fmt::println("Parsing shader: {}", shader.getInfoLog());

    glslang::TProgram program;
    program.addShader(&shader);
    program.link(EShMsgDefault);

    fmt::println("Linking Program: {}", program.getInfoLog());

    glslang::TIntermediate *intermediate = program.getIntermediate(stage);
    std::vector<u32> SPIRVBinary;
    glslang::GlslangToSpv(*intermediate, SPIRVBinary);
    glslang::FinalizeProcess();

    fmt::println("Sizeof u32: {}", sizeof(u32));
    fmt::println("Sizeof u8:  {}", sizeof(u8));
    fmt::println("Size:  {}", (sizeof(u32) / sizeof(u8)));
    fmt::println("Size:  {}", SPIRVBinary.size() * (sizeof(u32) / sizeof(u8)));
    const auto size = static_cast<i32>(SPIRVBinary.size() * (sizeof(u32) / sizeof(u8)));

    glslang::OutputSpvBin(SPIRVBinary, "output.bin");

    fmt::println("Original size: {} vs the new size: {}", SPIRVBinary.size(), size);

#if 1
    glShaderBinary(1, &m_descriptor, GL_SHADER_BINARY_FORMAT_SPIR_V, SPIRVBinary.data(), size);
#else
    glShaderBinary(1, &m_descriptor, GL_SHADER_BINARY_FORMAT_SPIR_V, SPIRVBinary.data(), SPIRVBinary.size());
#endif
    auto errCode = glGetError();
    fmt::println("Error: {}", errCode);
    // fmt::println("Error: {}", errCode == GL_INVALID_OPERATION);
    // fmt::println("Error: {}", errCode == GL_INVALID_ENUM);
    // fmt::println("Error: {}", errCode == GL_INVALID_VALUE);
    glSpecializeShader(m_descriptor, "main", 0, nullptr, nullptr);

    int isCompilationSuccess = 0;
    glGetShaderiv(m_descriptor, GL_COMPILE_STATUS, &isCompilationSuccess);
    if (not static_cast<bool>(isCompilationSuccess)) {
        auto msg = utils::getShaderErrorMessage(m_descriptor);
        throw std::runtime_error(
            fmt::format("Shader compilation was no successful: ({})", msg)
        );
    }

        GLint maxLength = 0;
    glGetShaderiv(m_descriptor, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(m_descriptor, maxLength, &maxLength, &infoLog[0]);

    std::string infoLogStr{infoLog.begin(), infoLog.end()};

    for (auto c : infoLog) {
        fmt::print("{}", c);
    }
    fmt::println("");
    fmt::println("{}", infoLogStr);

    fmt::println("Shader was successfully created");
#endif
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
