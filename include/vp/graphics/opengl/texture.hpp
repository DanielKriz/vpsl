#ifndef VP_TEXTURE_OPENGL_HPP
#define VP_TEXTURE_OPENGL_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <filesystem>

#include <SDL2/SDL_image.h>

#include <vp/types.hpp>
#include <vp/graphics/opengl/object.hpp>
#include <vp/description/texture_description.hpp>

namespace vp::gl::opengl {

#if 0
enum class TextureKind : enum32 {
    _1D = GL_TEXTURE_1D,
    _2D = GL_TEXTURE_2D,
    _3D = GL_TEXTURE_3D,
    Rectangle = GL_TEXTURE_RECTANGLE,
    CubeMap = GL_TEXTURE_CUBE_MAP,
    Array1D = GL_TEXTURE_1D_ARRAY,
    Array2D = GL_TEXTURE_2D_ARRAY,
    CubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
    Multisample2D = GL_TEXTURE_2D_MULTISAMPLE,
    MultisampleArray2D = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
};
#endif

// We need some kind of conversion from SDL
// https://wiki.libsdl.org/SDL2/SDL_PixelFormatEnum

class Texture {
public:
#if 0
    [[nodiscard]] const u8 *getData() const noexcept { return m_dataBuffer.data(); };
#endif
    [[nodiscard]] u32 getDescriptor() const noexcept;
    [[nodiscard]] u32 getLocation() const noexcept;

    static Texture createFromDescription(const desc::TextureDescription &desc);
private:
    Texture();
    u32 m_location { 0 };
    std::shared_ptr<u32> m_pDescriptor;
};

} // namespace vp::gl::opengl

#endif // VP_TEXTURE_OPENGL_HPP
