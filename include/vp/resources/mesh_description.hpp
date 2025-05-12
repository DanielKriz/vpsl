#ifndef VP_RESOURCES_MESH_DESCRIPTION_HPP
#define VP_RESOURCES_MESH_DESCRIPTION_HPP

#include <filesystem>

#include <glm/glm.hpp>

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp {
class MeshDescription {
public:
private:
    std::filesystem::path m_path;
    u8 m_ambient;
    u8 m_specular;
    u8 m_diffuse;
    u8 m_emmisive;
};

} // namespace vp

#endif // VP_RESOURCES_MESH_DESCRIPTION_HPP
