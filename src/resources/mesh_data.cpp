#include <vp/resources/mesh_data.hpp>

namespace vp {

MeshData::MeshData(const std::vector<gl::Vertex> &vertices)
{
    *m_pVertices = vertices;
}

void MeshData::setVertices(const std::vector<gl::Vertex> &vertices) {
    *m_pVertices = vertices;
}

void MeshData::setAttributeDescription(desc::AttributeDescription desc) {
    m_attrDesc = std::move(desc);
}

size MeshData::getVertexCount() const noexcept {
    return static_cast<size>(m_pVertices->size());
}

const std::vector<gl::Vertex> &MeshData::getVertices() const noexcept {
    return *m_pVertices;
}

const desc::AttributeDescription &MeshData::getAttributeDescription() const noexcept {
    return m_attrDesc;
}

} // namespace vp

