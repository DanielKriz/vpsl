#include <vp/description/attribute_description.hpp>

namespace vp {

std::ostream &operator<<(std::ostream &os, const AttributeType &type) {
    const std::string_view repr = [type]() {
        using enum AttributeType;
        switch (type) {
        case Position: return "Position";
        case Normal: return "Normal";
        case UV: return "UV";
        case Tangent: return "Tangent";
        case Bitangent: return "Bitangent";
        default:
            throw std::runtime_error("Unhandled attribute type for representation");
        }
    }();
    return os << repr;
}

u64 Attribute::elementCountFromType(AttributeType type) {
    if (type == AttributeType::UV) {
        return 2;
    }
    return 3;
}

u64 Attribute::offsetFromType(AttributeType type) {
    using enum AttributeType;
    switch (type) {
    case Position:
        return offsetof(gl::Vertex, position);
    case Normal:
        return offsetof(gl::Vertex, normal);
    case UV:
        return offsetof(gl::Vertex, uv);
    case Tangent:
        return offsetof(gl::Vertex, tangent);
    case Bitangent:
        return offsetof(gl::Vertex, bitangent);
    default:
        throw std::runtime_error(
            fmt::format("Unknown Attribute type: '{}'", type)
        );
    }
}

} // namespace vp

namespace vp::desc {

void AttributeDescription::addAttribute(AttributeType type, u32 location) {
    m_attributes.emplace_back(type, location);
}

const std::vector<Attribute> &AttributeDescription::getAttributes() const noexcept{
    return m_attributes;
}

std::ostream &operator<<(std::ostream &os, const Attribute &attr) {
    return os << "Attribute(" << attr.type << ", " << attr.location << ")";
}

std::ostream &operator<<(std::ostream &os, const AttributeDescription &desc) {
    const auto &attrs = desc.m_attributes;
    os << "AttributeDescription(";
    std::for_each(attrs.begin(), attrs.end() - 1, [&os](const Attribute &item) {
        os << item << ", ";
    });
    os << attrs.back() << ")";
    return os;
}

} // namespace vp::desc
