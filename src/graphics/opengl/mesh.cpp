#include <vp/graphics/opengl/mesh.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

namespace vp::gl::opengl {

Mesh::Mesh(const std::vector<Vertex> &vertices, const desc::AttributeDescription &desc)
    : m_pVertices(&vertices), m_attrDesc(desc)
{
    m_pVBO = std::shared_ptr<u32>(new u32, [](const u32 *pDesc) {
        glDeleteBuffers(1, pDesc);
        delete pDesc;
    });

    m_pVAO = std::shared_ptr<u32>(new u32, [](const u32 *pDesc) {
        glDeleteVertexArrays(1, pDesc);
        delete pDesc;
    });

    using namespace desc;
    glCreateBuffers(1, m_pVBO.get());
    glCreateVertexArrays(1, m_pVAO.get());

    auto &vao = *m_pVAO;
    auto &vbo = *m_pVBO;

    glNamedBufferData(vao, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);


    const auto &attributes = desc.getAttributes();
    for (u32 i = 0u; i < attributes.size(); ++i) {
        const auto &attribute = attributes[i];
        fmt::println("Setting up Attribute {} -> {}", attribute.type, attribute.location);
        glEnableVertexArrayAttrib(vao, i);
        glVertexArrayAttribBinding(vao, i, 0);
        const auto count = static_cast<i32>(Attribute::elementCountFromType(attribute.type));
        const auto offset = Attribute::offsetFromType(attribute.type);
        glVertexArrayAttribFormat(vao, i, count, GL_FLOAT, GL_FALSE, offset);
    }
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));
}

void Mesh::draw() const {
    glBindVertexArray(*m_pVAO);
    glDrawArrays(GL_TRIANGLES, 0, m_pVertices->size());

}

} // namespace vp::gl::opengl
