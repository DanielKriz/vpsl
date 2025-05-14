#include <vp/description/program_description.hpp>

namespace vp::desc {

ProgramDescriptionBuilder &ProgramDescriptionBuilder::addTexture(TextureDescription &desc) {
    m_programDesc.m_textures.push_back(&desc);
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setName(const std::string &name) {
    m_isNameSet = true;
    m_programDesc.m_name = name;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setNameFromID() {
    m_isNameSet = true;
    m_programDesc.m_name = std::to_string(m_id++);
    return *this;
}

std::string ProgramDescriptionBuilder::createShaderName(const std::string &originalName) const {
    if (not m_isNameSet) {
        throw std::runtime_error(
            "it is not possible to create shader name if program does not have name"
        );
    }
    return m_programDesc.m_name + ":" + originalName;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::addBuffer(BufferDescription &desc) {
    m_programDesc.m_buffers.push_back(&desc);
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::addShaderCode(ShaderCode &code) {
    m_programDesc.m_shaderCodes.push_back(&code);
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setOptions(const Options &opts) {
    m_programDesc.m_options = opts;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setOption(gl::PolygonMode mode) {
    m_programDesc.m_options.frontFacePolygonMode = mode;
    m_programDesc.m_options.backFacePolygonMode = mode;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setOption(
    gl::Face face,
    gl::PolygonMode mode
) {
    if (face == gl::Face::Front) {
        m_programDesc.m_options.frontFacePolygonMode = mode;
    }
    if (face == gl::Face::Back) {
        m_programDesc.m_options.backFacePolygonMode = mode;
    }
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setOption(gl::CullingMode mode) {
    m_programDesc.m_options.cullingMode = mode;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setOption(gl::FrontFaceMode mode) {
    m_programDesc.m_options.frontFaceMode = mode;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setOption(
    gl::BlendingFactor factor,
    bool isToSource
) {
    if (isToSource) {
        m_programDesc.m_options.srcBlendFactor = factor;
    } else {
        m_programDesc.m_options.dstBlendFactor = factor;
    }
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setOption(gl::DepthFunction mode) {
    m_programDesc.m_options.depthFunction = mode;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::enableDepthTest(bool isEnabled) {
    m_programDesc.m_options.isDepthTestEnabled = isEnabled;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::enableFaceCulling(bool isEnabled) {
    m_programDesc.m_options.isFaceCullingEnabled = isEnabled;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::enableBlending(bool isEnabled) {
    m_programDesc.m_options.isBlendingEnabled = isEnabled;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setFrameBuffer(
    FrameBufferDescription &desc
) {
    m_programDesc.m_pFrameBuffer = &desc;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::addMaterial(
    MaterialDescription &desc
) {
    m_programDesc.m_materials.push_back(&desc);
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::setMesh(
    MeshDescription &desc
) {
    m_programDesc.m_pMesh = &desc;
    return *this;
}

ProgramDescriptionBuilder &ProgramDescriptionBuilder::reset() {
    m_programDesc = ProgramDescription{};
    return *this;
}

ProgramDescription &&ProgramDescriptionBuilder::build() {
    m_isNameSet = false;
    return std::move(m_programDesc);
}

} // namespace vp::desc
