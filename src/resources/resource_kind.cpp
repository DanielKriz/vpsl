#include <vp/resources/resource_kind.hpp>

namespace vp {

std::ostream &operator<<(std::ostream &os, const vp::ResourceKind &kind) {
    const std::string_view repr = [kind]() {
        using enum vp::ResourceKind;
        switch (kind) {
        case Mesh: return "Mesh";
        case Material: return "Material";
        case Texture: return "Texture";
        default:
            throw std::runtime_error("Unknown Resource kind for representation");
        }
    }();
    return os << repr;
}

} // namespace vp
