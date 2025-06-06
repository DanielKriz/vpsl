#include <vp/graphics/opengl/mesh.hpp>

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

    const auto bufferSizeInBytes = static_cast<sptr>(sizeof(Vertex) * vertices.size());
    glNamedBufferData(vao, bufferSizeInBytes, vertices.data(), GL_STATIC_DRAW);

    const auto &attributes = desc.getAttributes();
    for (u32 i = 0u; i < attributes.size(); ++i) {
        const auto &attribute = attributes[i];
        glEnableVertexArrayAttrib(vao, i);
        const auto count = static_cast<i32>(Attribute::elementCountFromType(attribute.type));
        const auto offset = Attribute::offsetFromType(attribute.type);
        glVertexArrayAttribFormat(vao, i, count, GL_FLOAT, GL_FALSE, static_cast<u32>(offset));
        glVertexArrayAttribBinding(vao, i, 0);
    }
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));
}

void Mesh::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, *m_pVBO);
    glBindVertexArray(*m_pVAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<size>(m_pVertices->size()));
}

} // namespace vp::gl::opengl
