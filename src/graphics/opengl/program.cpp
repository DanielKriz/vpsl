#include <vp/graphics/opengl/program.hpp>
#include <vp/graphics/opengl/uniform.hpp>

#include <fmt/core.h>

namespace vp::gl::opengl {

Program::Program() : Object() {
    m_descriptor = glCreateProgram();
}

Program::~Program() {
    glDeleteProgram(m_descriptor);
}

Program& Program::link() {
    glLinkProgram(m_descriptor);
    return *this;
}

void Program::use() const {
    glUseProgram(m_descriptor);
}

Program &Program::attachShader(Shader &shader) {
    glAttachShader(m_descriptor, shader.getDescriptor());
    return *this;
}

Program &Program::detachShader(Shader &shader) {
    glDetachShader(m_descriptor, shader.getDescriptor());
    return *this;
}

void Program::populateAttributes() {

}

void Program::populateUniforms() {

}

void Program::addTextureFromDescription(const desc::TextureDescription &desc) {
    m_textures.emplace_back(Texture::createFromDescription(desc));
}

void Program::addTexture(Texture &texture) {
    m_textures.push_back(texture);
}

void Program::setDrawCommand(const DrawCommand &command) {
    m_drawCommand = command;
}

void Program::initMesh(
    const std::vector<Vertex> &vertices,
    const desc::AttributeDescription &desc
) {
    m_pMesh = std::make_shared<Mesh>(vertices, desc);
}

void Program::draw() const {

    for (u32 i = 0u; i < m_textures.size(); ++i) {
        glBindTextureUnit(m_textures[i].getLocation(), m_textures[i].getDescriptor());
        auto uniform = Uniform("", m_textures[i].getLocation());
        uniform.set<i32>(m_textures[i].getDescriptor());
    }

    if (m_pMesh != nullptr) {
        m_pMesh->draw();
        return;
    }

    // IF MESH
    // IF DRAW
    const auto &command = *m_drawCommand;
    const i32 count = static_cast<i32>(command.count);
    using enum DrawMode;
    switch (command.mode) {
    case Points:
        glDrawArrays(GL_POINTS, 0, count);
        break;
    case LineStrip:
        glDrawArrays(GL_LINE_STRIP, 0, count);
        break;
    case LineLoop:
        glDrawArrays(GL_LINE_LOOP, 0, count);
        break;
    case Lines:
        glDrawArrays(GL_LINES, 0, count);
        break;
    case LineStripAdjacency:
        glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, count);
        break;
    case LinesAdjacency:
        glDrawArrays(GL_LINES_ADJACENCY, 0, count);
        break;
    case TriangleStrip:
        glDrawArrays(GL_TRIANGLE_STRIP, 0, count);
        break;
    case TriangleFan:
        glDrawArrays(GL_TRIANGLE_FAN, 0, count);
        break;
    case Triangles:
        glDrawArrays(GL_TRIANGLES, 0, count);
        break;
    case TriangleStripAdjacency:
        glDrawArrays(GL_TRIANGLE_STRIP_ADJACENCY, 0, count);
        break;
    case TrianglesAdjacency:
        glDrawArrays(GL_TRIANGLES_ADJACENCY, 0, count);
        break;
    case Patches:
        glDrawArrays(GL_PATCHES, 0, count);
        break;
    }
}

} // namespace vp::gl::opengl
