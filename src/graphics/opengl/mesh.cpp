#include <vp/graphics/opengl/mesh.hpp>

namespace vp::gl::opengl {

Mesh::Mesh(const std::vector<Vertex> &vertices, const desc::AttributeDescription &desc) {
    m_pVertices = &vertices;
    m_attrDesc = desc;
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
    glNamedBufferStorage(
        *m_pVBO,
        static_cast<size>(sizeof(Vertex) * vertices.size()),
        vertices.data(),
        GL_DYNAMIC_STORAGE_BIT
    );

    glCreateVertexArrays(1, m_pVAO.get());
    glVertexArrayVertexBuffer(*m_pVAO, 0, *m_pVBO, 0, sizeof(Vertex));

    const auto &attributes = desc.getAttributes();
    for (u32 i = 0u; i < attributes.size(); ++i) {
        const auto &attribute = attributes[i];
        fmt::println("Setting up Attribute {} -> {}", attribute.type, attribute.location);
        glEnableVertexArrayAttrib(*m_pVAO, i);
        glVertexArrayAttribFormat(
            *m_pVAO,
            i,
            static_cast<i32>(Attribute::elementCountFromType(attribute.type)),
            GL_FLOAT,
            GL_FALSE,
            Attribute::offsetFromType(attribute.type)
        );
        glVertexArrayAttribBinding(*m_pVAO, i, attribute.location);
    }
}

void Mesh::draw() const {
    glBindVertexArray(*m_pVAO);

    glBindBuffer(GL_ARRAY_BUFFER, *m_pVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        m_pVertices->size() * sizeof(Vertex),
        m_pVertices->data(),
        GL_STATIC_DRAW
    );

    const auto &attributes = m_attrDesc.getAttributes();
    for (u32 i = 0; i < attributes.size(); ++i) {
        glVertexArrayAttribBinding(*m_pVAO, i, attributes[i].location);
    }
    glDrawArrays(GL_TRIANGLES, 0, m_pVertices->size());

}

} // namespace vp::gl::opengl
