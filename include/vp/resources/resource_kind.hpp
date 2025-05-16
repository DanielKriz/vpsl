#ifndef VP_RESOURCE_RESOURCE_KIND_HPP
#define VP_RESOURCE_RESOURCE_KIND_HPP

#include <iosfwd>

#include <fmt/ostream.h>

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp {

enum class ResourceKind : u8 {
    Mesh,
    Texture,
    Material,
};

std::ostream &operator<<(std::ostream &os, const vp::ResourceKind &kind);

template <>
inline utils::StringViewMap<ResourceKind> utils::StringToEnumMap<ResourceKind>::map = {
    { "material", ResourceKind::Material },
    { "mesh", ResourceKind::Mesh },
    { "texture", ResourceKind::Texture },
};

} // namespace vp

template <>
struct fmt::formatter<vp::ResourceKind> : ostream_formatter {};

#endif // VP_RESOURCE_RESOURCE_KIND_HPP
