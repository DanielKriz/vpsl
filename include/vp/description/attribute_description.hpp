#ifndef VP_DESCRIPTION_ATTRIBUTE_DESCRIPTION_HPP
#define VP_DESCRIPTION_ATTRIBUTE_DESCRIPTION_HPP

#include <vector>

#include <fmt/ostream.h>

#include <vp/graphics/vertex.hpp>
#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp {

enum class AttributeType : u8 {
    Position,
    Normal,
    UV,
    Tangent,
    Bitangent,
};

template <>
inline utils::StringViewMap<AttributeType> utils::StringToEnumMap<AttributeType>::map = {
    { "position" , AttributeType::Position },
    { "xyz" , AttributeType::Position },
    { "uv" , AttributeType::UV },
    { "normal" , AttributeType::Normal },
    { "tangent" , AttributeType::Tangent },
    { "bitangent" , AttributeType::Bitangent },
};

std::ostream &operator<<(std::ostream &os, const AttributeType &type);

struct Attribute {
    AttributeType type;
    u32 location;

    static u64 elementCountFromType(AttributeType type);
    static u64 offsetFromType(AttributeType type);
};

} // namespace vp

namespace vp::desc {

std::ostream &operator<<(std::ostream &os, const Attribute &type);

class AttributeDescription final {
public:
    void addAttribute(AttributeType type, u32 location);
    [[nodiscard]] const std::vector<Attribute> &getAttributes() const noexcept;

    friend std::ostream &operator<<(std::ostream &os, const AttributeDescription &desc);
private:
    std::vector<Attribute> m_attributes;
};

} // namespace vp::desc

template <>
struct fmt::formatter<vp::AttributeType> : ostream_formatter {};

template <>
struct fmt::formatter<vp::Attribute> : ostream_formatter {};

template <>
struct fmt::formatter<vp::desc::AttributeDescription> : ostream_formatter {};

#endif // VP_DESCRIPTION_ATTRIBUTE_DESCRIPTION_HPP
