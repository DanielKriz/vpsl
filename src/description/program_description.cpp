#include <vp/description/program_description.hpp>

namespace vp::desc {

const std::string &ProgramDescription::getName() const noexcept {
    return m_name;
}

const std::vector<TextureDescription> &
ProgramDescription::getTextures() const noexcept {
    return m_textures;
}

const std::vector<MaterialData *> &
ProgramDescription::getMaterialDescriptions() const noexcept {
    return m_materials;
}

const std::vector<BufferDescription *> &
ProgramDescription::getBufferDescriptions() const noexcept {
    return m_buffers;
}

const std::vector<ShaderCode *> &ProgramDescription::getShaderCodes() const noexcept {
    return m_shaderCodes;
}

const Options &ProgramDescription::getOptions() const {
    return m_options;
}

bool ProgramDescription::hasFrameBuffer() const {
    return (m_pFrameBuffer != nullptr);
}

bool ProgramDescription::hasMesh() const {
    return (m_pMesh != nullptr);
}

const FrameBufferDescription &ProgramDescription::getFrameBufferDescription() const {
    if (m_pFrameBuffer == nullptr) {
        throw std::runtime_error("This program description does not have frame buffer");
    }
    return *m_pFrameBuffer;
}

const MeshDescription &ProgramDescription::getMeshDescription() const {
    if (m_pMesh == nullptr) {
        throw std::runtime_error("This program description does not have a mesh");
    }
    return *m_pMesh;
}

const DrawCommand &ProgramDescription::getDrawCommand() const {
    if (hasDrawCommand()) {
        return *m_drawCommand;
    }
    throw std::runtime_error("Draw command is not defined for this program!");
}

bool ProgramDescription::hasDrawCommand() const noexcept {
    return m_drawCommand.has_value();
}

} // namespace vp::desc
