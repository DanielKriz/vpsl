#include <vp/resources/texture.hpp>

#include <doctest/doctest.h>

#include <sstream>

using namespace vp;

TEST_SUITE("Texture") {

TEST_CASE("String representation of kind unknown") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::Unknown);
    CHECK(ss.str() == "Unknown");
}

TEST_CASE("String representation of kind 1D") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::_1D);
    CHECK(ss.str() == "1D");
}

TEST_CASE("String representation of kind 2D") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::_2D);
    CHECK(ss.str() == "2D");
}

TEST_CASE("String representation of kind 3D") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::_3D);
    CHECK(ss.str() == "3D");
}

TEST_CASE("String representation of kind Rectangle") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::Rectangle);
    CHECK(ss.str() == "Rectangle");
}

TEST_CASE("String representation of kind CubeMap") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::CubeMap);
    CHECK(ss.str() == "CubeMap");
}

TEST_CASE("String representation of kind Array1D") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::Array1D);
    CHECK(ss.str() == "Array1D");
}

TEST_CASE("String representation of kind Array2D") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::Array2D);
    CHECK(ss.str() == "Array2D");
}

TEST_CASE("String representation of kind CubeMapArray") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::CubeMapArray);
    CHECK(ss.str() == "CubeMapArray");
}

TEST_CASE("String representation of kind Multisample2D") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::Multisample2D);
    CHECK(ss.str() == "Multisample2D");
}

TEST_CASE("String representation of kind MultisampleArray2D") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureKind::MultisampleArray2D);
    CHECK(ss.str() == "MultisampleArray2D");
}

TEST_CASE("String representation of format Unknown") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureFormat::Unknown);
    CHECK(ss.str() == "Unknown");
}

TEST_CASE("String representation of format RGBA") {
    std::stringstream ss;
    CHECK_NOTHROW(ss << TextureFormat::RGBA);
    CHECK(ss.str() == "RGBA");
}

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
