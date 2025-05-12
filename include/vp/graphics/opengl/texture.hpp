#ifndef VP_TEXTURE_OPENGL_HPP
#define VP_TEXTURE_OPENGL_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <filesystem>

#include <SDL2/SDL_image.h>

#include <vp/types.hpp>
#include <vp/graphics/opengl/object.hpp>

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

class Texture : public opengl::Object {
public:
    Texture() = default;
    Texture(std::filesystem::path path) {
        glGenTextures(1, &m_descriptor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, m_descriptor);

        SDL_Surface *tex_surface = IMG_Load(path.c_str());
        if (tex_surface == nullptr) {
            throw std::runtime_error("Could not load texture");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_surface->w, tex_surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        SDL_FreeSurface(tex_surface);
        tex_surface = nullptr;
    }
    // [[nodiscard]] inline const TextureKind &getKind() const noexcept { return m_kind ; }
    [[nodiscard]] inline const u8 *getData() const noexcept { return m_dataBuffer.data(); };
    [[nodiscard]] const std::string &getName() const { return m_name; }
private:
    std::vector<u8> m_dataBuffer;
    // TextureKind m_kind;
    std::string m_name;
};

} // namespace vp::gl

#endif // VP_TEXTURE_OPENGL_HPP
