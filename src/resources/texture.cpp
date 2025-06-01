#include <iostream>

#include <vp/resources/texture.hpp>

namespace vp {

std::ostream &operator<<(std::ostream &os, const TextureFormat &format) {
    const std::string_view formatRepr = [&format]() {
        using enum TextureFormat;
        switch (format) {
        case TextureFormat::Unknown: return "Unknown";
        case TextureFormat::RGBA: return "RGBA";
        default:
            throw std::runtime_error("Unknown texture format for representation");
        }
    }();
    return os << formatRepr;
}

std::ostream &operator<<(std::ostream &os, const TextureKind &kind) {
    const std::string_view textureRepr = [&kind]() {
        using enum TextureKind;
        switch (kind) {
        case TextureKind::Unknown: return "Unknown";
        case TextureKind::_1D: return "1D";
        case TextureKind::_2D: return "2D";
        case TextureKind::_3D: return "3D";
        case TextureKind::Rectangle: return "Rectangle";
        case TextureKind::CubeMap: return "CubeMap";
        case TextureKind::Array1D: return "Array1D";
        case TextureKind::Array2D: return "Array2D";
        case TextureKind::CubeMapArray: return "CubeMapArray";
        case TextureKind::Multisample2D: return "Multisample2D";
        case TextureKind::MultisampleArray2D: return "MultisampleArray2D";
        default:
            throw std::runtime_error("Unknown texture kind for representation");
        }
    }();
    return os << textureRepr;
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
