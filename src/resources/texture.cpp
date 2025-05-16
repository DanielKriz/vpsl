#include <iostream>

#include <vp/resources/texture.hpp>

namespace vp {

std::ostream &operator<<(std::ostream &os, const TextureFormat &format) {
}

std::ostream &operator<<(std::ostream &os, const TextureKind &kind) {
}

Texture::Texture(TextureKind kind, TextureFormat format, SDL_Surface *pSurf)
    : m_kind(kind), m_format(format), m_pData(pSurf, sdl::deleteSurface)
{}

Texture::Texture(SDL_Surface *pSurf)
    : m_pData(pSurf, sdl::deleteSurface)
{}

Texture::Texture(TextureKind kind, TextureFormat format)
    : m_kind(kind), m_format(format)
{}

void Texture::setFormat(TextureFormat format) noexcept {
    m_format = format;
}

void Texture::setKind(TextureKind kind) noexcept {
    m_kind = kind;
}

void Texture::setData(SDL_Surface *pSurface) noexcept {
    m_pData.reset(pSurface);
}

void Texture::setData(std::shared_ptr<SDL_Surface> pSurface) noexcept {
    m_pData = std::move(pSurface);
}

const TextureFormat &Texture::getFormat() const noexcept {
    return m_format;
}

const TextureKind &Texture::getKind() const noexcept {
    return m_kind;
}

SDL_Surface *Texture::getData() noexcept {
    return m_pData.get();
}

std::shared_ptr<SDL_Surface> Texture::shareData() noexcept {
    return m_pData;
}

bool Texture::isValid() const noexcept {
    return m_pData != nullptr;
}

} // namespace vp
