#ifndef VP_RESOURCES_MESH_DATA_HPP
#define VP_RESOURCES_MESH_DATA_HPP

#include <vp/description/attribute_description.hpp>
#include <vp/graphics/vertex.hpp>
#include <vp/types.hpp>

namespace vp {

class MeshData {
public:
    MeshData() = default;
    MeshData(const std::vector<gl::Vertex> &vertices);

    void setVertices(const std::vector<gl::Vertex> &vertices);
    void setAttributeDescription(desc::AttributeDescription desc);

    [[nodiscard]] size getVertexCount() const noexcept;
    [[nodiscard]] const std::vector<gl::Vertex> &getVertices() const noexcept;
    [[nodiscard]] const desc::AttributeDescription &getAttributeDescription() const noexcept;
private:
    std::shared_ptr<std::vector<gl::Vertex>> m_pVertices { std::make_shared<std::vector<gl::Vertex>>() };
    desc::AttributeDescription m_attrDesc;
};

} // namespace vp

#endif // VP_RESOURCES_MESH_DATA_HPP
