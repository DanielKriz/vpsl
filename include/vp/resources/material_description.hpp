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
};

} // namespace vp

#endif // VP_RESOURCES_MATERIAL_DESCRIPTION_HPP
