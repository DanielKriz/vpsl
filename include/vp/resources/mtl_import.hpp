#ifndef VP_RESOURCES_MTL_IMPORT_HPP
#define VP_RESOURCES_MTL_IMPORT_HPP

#include <filesystem>

#include <vp/resources/material_data.hpp>

namespace vp::mtl {

MaterialData import(std::istream &is);
MaterialData importFromFile(const std::filesystem::path &path);

} // namespace vp::mtl

#endif // VP_RESOURCES_MTL_IMPORT_HPP
