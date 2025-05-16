#include <vp/graphics/opengl/texture.hpp>

#include <spdlog/spdlog.h>

namespace vp::gl::opengl {

Texture::Texture() {
    m_pDescriptor = std::shared_ptr<u32>(new u32, [](const u32 *pDesc){
            glDeleteTextures(1, pDesc);
            delete pDesc;
    });
    glCreateTextures(GL_TEXTURE_2D, 1, m_pDescriptor.get());
}

u32 Texture::getDescriptor() const noexcept {
    return *m_pDescriptor;
}

u32 Texture::getLocation() const noexcept {
    return m_location;
}

Texture Texture::createFromDescription(const desc::TextureDescription &desc) {
    Texture texture;
    glTextureParameteri(texture.getDescriptor(), GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTextureParameteri(texture.getDescriptor(), GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTextureParameteri(texture.getDescriptor(), GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(texture.getDescriptor(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_Surface *pSurface = desc.pTexture->getData();
    SDL_Surface *pTmpSurface = SDL_ConvertSurfaceFormat(pSurface, SDL_PIXELFORMAT_RGBA8888, 0);

#if !NDEBUG
    fmt::println("Format name:     {}", SDL_GetPixelFormatName(pSurface->format->format));
    fmt::println("Bytes per pixel: {}", pSurface->format->BytesPerPixel);
#endif

    glTextureStorage2D(texture.getDescriptor(), 1, GL_RGBA8, pTmpSurface->w, pTmpSurface->h);
    glTextureSubImage2D(
        texture.getDescriptor(), 0, 0, 0, pTmpSurface->w, pTmpSurface->h,
        GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, pTmpSurface->pixels
    );
    glGenerateTextureMipmap(texture.getDescriptor());

    SDL_FreeSurface(pTmpSurface);
    texture.m_location = desc.location;

    return texture;
}

} // namespace vp::gl::opengl
