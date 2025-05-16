#ifndef VP_RESOURCES_LOAD_REQUEST_HPP
#define VP_RESOURCES_LOAD_REQUEST_HPP

#include <filesystem>

#include <vp/resources/resource_kind.hpp>

namespace vp {

struct LoadRequest {
    ResourceKind type;
    std::string name;
    std::filesystem::path path;
};

} // namespace vp

#endif // VP_RESOURCES_LOAD_REQUEST_HPP
