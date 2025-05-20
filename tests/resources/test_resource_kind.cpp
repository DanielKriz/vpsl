#include <vp/resources/resource_kind.hpp>

#include <doctest/doctest.h>

using namespace vp;

TEST_SUITE("Resource Kind") {

TEST_CASE("Resource kind string representation of Mesh") {
    std::stringstream ss;
    ss << ResourceKind::Mesh;
    CHECK(ss.str() == "Mesh");
}

TEST_CASE("Resource kind string representation of Material") {
    std::stringstream ss;
    ss << ResourceKind::Material;
    CHECK(ss.str() == "Material");
}

TEST_CASE("Resource kind string representation of Texture") {
    std::stringstream ss;
    ss << ResourceKind::Texture;
    CHECK(ss.str() == "Texture");
}

}
