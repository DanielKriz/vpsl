#ifndef VP_DESCRIPTION_ATTRIBUTE_DESCRIPTION_HPP
#define VP_DESCRIPTION_ATTRIBUTE_DESCRIPTION_HPP

#include <vp/types.hpp>

namespace vp::desc {

enum class AttributeType : u8 {
    Position,
    Normal,
    UV,
    Tangent,
    Bitangent,
};

class AttributeDescription final {
public:
private:
};

} // namespace vp::desc

#endif // VP_DESCRIPTION_ATTRIBUTE_DESCRIPTION_HPP
