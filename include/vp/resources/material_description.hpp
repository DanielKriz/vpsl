#ifndef VP_RESOURCES_MATERIAL_DESCRIPTION_HPP
#define VP_RESOURCES_MATERIAL_DESCRIPTION_HPP

#include <filesystem>

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp {
class MaterialDescription {
public:
private:
    std::filesystem::path m_path;
    u8 m_ambient;
    u8 m_specular;
    u8 m_emmisive;
    u8 m_diffuse;
};

} // namespace vp

#endif // VP_RESOURCES_MATERIAL_DESCRIPTION_HPP
