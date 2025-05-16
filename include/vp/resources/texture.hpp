#ifndef VP_RESOURCES_TEXTURE_HPP
#define VP_RESOURCES_TEXTURE_HPP

#include <filesystem>
#include <functional>
#include <iosfwd>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp::sdl {

using SurfaceDeleter = std::function<void(SDL_Surface *)>;

inline void deleteSurface(SDL_Surface *pSurface) {
    SDL_FreeSurface(pSurface);
}

} // namespace vp::sdl

namespace vp {

enum class TextureFormat : u8 {
    Unknown,
    RGBA,
};

template <>
inline utils::StringViewMap<TextureFormat> utils::StringToEnumMap<TextureFormat>::map = {
    { "rgba" , TextureFormat::RGBA },
};

std::ostream &operator<<(std::ostream &os, const TextureFormat &format);

enum class TextureKind : u8 {
    Unknown,
    _1D,
    _2D,
    _3D,
    Rectangle,
    CubeMap,
    Array1D,
    Array2D,
    CubeMapArray,
    Multisample2D,
    MultisampleArray2D,
};

template <>
inline utils::StringViewMap<TextureKind> utils::StringToEnumMap<TextureKind>::map = {
    { "1D" , TextureKind::_1D },
    { "2D" , TextureKind::_2D },
    { "3D" , TextureKind::_3D },
    { "rectangle" , TextureKind::Rectangle },
    { "cube_map" , TextureKind::CubeMap },
    { "array_1D" , TextureKind::Array1D },
    { "array_2D" , TextureKind::Array2D },
    { "cube_map_array" , TextureKind::CubeMapArray },
    { "multisample_2D" , TextureKind::Multisample2D },
    { "multisample_array_2D" , TextureKind::MultisampleArray2D },
};

std::ostream &operator<<(std::ostream &os, const TextureKind &kind);

class Texture final {
public:
    Texture() = default;
    Texture(TextureKind kind, TextureFormat format);
    Texture(TextureKind kind, TextureFormat format, SDL_Surface *pSurface);
    explicit Texture(SDL_Surface *pSurface);

    void setFormat(TextureFormat format) noexcept;
    void setKind(TextureKind kind) noexcept;
    void setData(SDL_Surface *pSurface) noexcept;
    void setData(std::shared_ptr<SDL_Surface> pSurface) noexcept;

    [[nodiscard]] const TextureFormat &getFormat() const noexcept;
    [[nodiscard]] const TextureKind &getKind() const noexcept;
    [[nodiscard]] SDL_Surface *getData() noexcept;
    [[nodiscard]] std::shared_ptr<SDL_Surface> shareData() noexcept;

    [[nodiscard]] bool isValid() const noexcept;
private:
    TextureKind m_kind { TextureKind::Unknown };
    TextureFormat m_format { TextureFormat::Unknown };
    std::shared_ptr<SDL_Surface> m_pData { nullptr, sdl::deleteSurface };
};

} // namespace vp

#endif // VP_RESOURCES_TEXTURE_HPP
