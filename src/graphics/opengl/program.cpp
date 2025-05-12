#include <vp/graphics/opengl/program.hpp>
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

} // namespace vp::gl::opengl
