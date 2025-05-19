#include <doctest/doctest.h>

#include <vp/resources/mtl_import.hpp>

TEST_SUITE("Material Importer") {

TEST_CASE("import data from file") {
const std::string src = R"(
newmtl Material
Ns 250.000000
Ka 1.000000 1.000000 1.000000
Kd 0.800000 0.800000 0.800000
Ks 0.500000 0.500000 0.500000
Ke 0.000000 0.000000 0.000000
Ni 1.450000
d 1.000000
illum 2
)";
    std::istringstream ss(src);

    auto data = vp::mtl::import(ss);
    CHECK(data.getAmbient() == glm::vec3(1.0f, 1.0f, 1.0f));
    CHECK(data.getDiffuse() == glm::vec3(0.8f, 0.8f, 0.8f));
    CHECK(data.getSpecular() == glm::vec3(0.5f, 0.5f, 0.5f));
    CHECK(data.getEmissive() == glm::vec3(0.0f, 0.0f, 0.0f));
}

}
