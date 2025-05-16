#ifndef VP_RESOURCES_MESH_DESCRIPTION_HPP
#define VP_RESOURCES_MESH_DESCRIPTION_HPP

#include <filesystem>

#include <glm/glm.hpp>

#include <vp/description/attribute_description.hpp>
#include <vp/graphics/vertex.hpp>
#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp {

class MeshDescription {
public:
    [[nodiscard]] size &getVertexCount() const noexcept;
    [[nodiscard]] const std::vector<gl::Vertex> &getVertices() const noexcept;
    [[nodiscard]] const desc::AttributeDescription &getAttributeDescription() const noexcept;
private:
    std::filesystem::path m_path;
    std::vector<gl::Vertex> m_vertices;
    desc::AttributeDescription m_attrDesc;
};

} // namespace vp

#endif // VP_RESOURCES_MESH_DESCRIPTION_HPP
