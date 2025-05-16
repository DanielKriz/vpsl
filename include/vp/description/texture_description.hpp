#ifndef VP_DESCRIPTION_TEXTURE_DESCRIPTION_HPP
#define VP_DESCRIPTION_TEXTURE_DESCRIPTION_HPP

#include <vp/resources/texture.hpp>
#include <vp/types.hpp>

namespace vp::desc {

struct TextureDescription {
    u32 location { 0 };
    Texture *pTexture { nullptr };
    TextureKind kind { TextureKind::_2D };
    TextureFormat format { TextureFormat::RGBA };
};

constexpr bool operator==(const TextureDescription &lhs, const TextureDescription &rhs) {
    return (lhs.location == rhs.location and lhs.pTexture == rhs.pTexture
            and lhs.kind == rhs.kind and lhs.format == rhs.format);
}

} // namespace vp::desc

#endif // VP_DESCRIPTION_TEXTURE_DESCRIPTION_HPP
