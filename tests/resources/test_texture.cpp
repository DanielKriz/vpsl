#include <vp/resources/texture.hpp>

#include <doctest/doctest.h>

using namespace vp;

TEST_SUITE("Texture") {

TEST_CASE("Simple Constructor") {
    SDL_Surface *pSurf = nullptr;
    CHECK_NOTHROW(auto texture = Texture(pSurf));
}

TEST_CASE("Complete Constructor") {
    SDL_Surface *pSurf = nullptr;
    CHECK_NOTHROW(auto texture = Texture(TextureKind::_1D, TextureFormat::RGBA, pSurf));
}

TEST_CASE("Constructor without surface") {
    CHECK_NOTHROW(auto texture = Texture(TextureKind::_1D, TextureFormat::RGBA));
}

TEST_CASE("It is possible to get the format") {
    auto texture = Texture(nullptr);
    CHECK(texture.getFormat() == TextureFormat::Unknown);
}

TEST_CASE("It is possible to get the kind") {
    auto texture = Texture(nullptr);
    CHECK(texture.getKind() == TextureKind::Unknown);
}

TEST_CASE("It is possible to get the pointer to surface") {
    auto texture = Texture(nullptr);
    CHECK(texture.getData() == nullptr);
}

TEST_CASE("It is possible to set the format") {
    auto texture = Texture(nullptr);
    texture.setFormat(TextureFormat::RGBA);
    CHECK(texture.getFormat() == TextureFormat::RGBA);
}

TEST_CASE("It is possible to set the kind") {
    auto texture = Texture(nullptr);
    texture.setKind(TextureKind::Array1D);
    CHECK(texture.getKind() == TextureKind::Array1D);
}

TEST_CASE("Surface is not valid for fresh texture") {
    auto texture = Texture(nullptr);
    CHECK_FALSE(texture.isValid());
}

TEST_CASE("It is possible to get the shared pointer to data from texture") {
    auto texture = Texture(nullptr);
    auto ptr = texture.shareData();
    CHECK(ptr == nullptr);
}

}
