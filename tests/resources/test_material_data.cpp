#include <vp/resources/material_data.hpp>

#include <sstream>

#include <doctest/doctest.h>

using namespace vp;

static inline MaterialData createMaterialData() {
    return {
        glm::vec3(1, 2, 3),
        glm::vec3(4, 5, 6),
        glm::vec3(7, 8, 9),
        glm::vec3(10, 11, 12),
        42.0f
    };
}

TEST_SUITE("Material Data") {

TEST_CASE("Default constructor of material data") {
    CHECK_NOTHROW(MaterialData{});
}

TEST_CASE("Complete constructor of material data") {
    CHECK_NOTHROW(MaterialData{
        glm::vec3(1, 2, 3),
        glm::vec3(4, 5, 6),
        glm::vec3(7, 8, 9),
        glm::vec3(10, 11, 12),
        42.0f
    });
}

TEST_CASE("It is possible to get ambient from material data") {
    auto data = createMaterialData();
    const auto &ambient = data.getAmbient();
    CHECK(ambient.x == doctest::Approx(1));
    CHECK(ambient.y == doctest::Approx(2));
    CHECK(ambient.z == doctest::Approx(3));
}

TEST_CASE("It is possible to get specular from material data") {
    auto data = createMaterialData();
    const auto &specular = data.getSpecular();
    CHECK(specular.x == doctest::Approx(4));
    CHECK(specular.y == doctest::Approx(5));
    CHECK(specular.z == doctest::Approx(6));
}

TEST_CASE("It is possible to get diffuse from material data") {
    auto data = createMaterialData();
    const auto &diffuse = data.getDiffuse();
    CHECK(diffuse.x == doctest::Approx(7));
    CHECK(diffuse.y == doctest::Approx(8));
    CHECK(diffuse.z == doctest::Approx(9));
}

TEST_CASE("It is possible to get emissive from material data") {
    auto data = createMaterialData();
    const auto &emissive = data.getEmissive();
    CHECK(emissive.x == doctest::Approx(10));
    CHECK(emissive.y == doctest::Approx(11));
    CHECK(emissive.z == doctest::Approx(12));
}

TEST_CASE("It is possible to get shininess from material data") {
    auto data = createMaterialData();
    const auto shininess = data.getShininess();
    CHECK(shininess == doctest::Approx(42));
}

TEST_CASE("Default values of material data") {
    auto data = MaterialData{};

    const auto &ambient = data.getAmbient();
    CHECK(ambient.x == doctest::Approx(0));
    CHECK(ambient.y == doctest::Approx(0));
    CHECK(ambient.z == doctest::Approx(0));

    const auto &specular = data.getSpecular();
    CHECK(specular.x == doctest::Approx(0));
    CHECK(specular.y == doctest::Approx(0));
    CHECK(specular.z == doctest::Approx(0));

    const auto &diffuse = data.getDiffuse();
    CHECK(diffuse.x == doctest::Approx(0));
    CHECK(diffuse.y == doctest::Approx(0));
    CHECK(diffuse.z == doctest::Approx(0));

    const auto &emissive = data.getEmissive();
    CHECK(emissive.x == doctest::Approx(0));
    CHECK(emissive.y == doctest::Approx(0));
    CHECK(emissive.z == doctest::Approx(0));

    const auto shininess = data.getShininess();
    CHECK(shininess == doctest::Approx(0));
}

TEST_CASE("It is possible to set the ambient to the material data") {
    auto data = MaterialData{};
    data.setAmbient(glm::vec3(1, 1, 1));
    const auto &ambient = data.getAmbient();
    CHECK(ambient.x == doctest::Approx(1));
    CHECK(ambient.y == doctest::Approx(1));
    CHECK(ambient.z == doctest::Approx(1));
}

TEST_CASE("It is possible to set the specular to the material data") {
    auto data = MaterialData{};
    data.setSpecular(glm::vec3(1, 1, 1));
    const auto &specular = data.getSpecular();
    CHECK(specular.x == doctest::Approx(1));
    CHECK(specular.y == doctest::Approx(1));
    CHECK(specular.z == doctest::Approx(1));
}

TEST_CASE("It is possible to set the diffuse to the material data") {
    auto data = MaterialData{};
    data.setDiffuse(glm::vec3(1, 1, 1));
    const auto &diffuse = data.getDiffuse();
    CHECK(diffuse.x == doctest::Approx(1));
    CHECK(diffuse.y == doctest::Approx(1));
    CHECK(diffuse.z == doctest::Approx(1));
}

TEST_CASE("It is possible to set the emissive to the material data") {
    auto data = MaterialData{};
    data.setEmissive(glm::vec3(1, 1, 1));
    const auto &emissive = data.getEmissive();
    CHECK(emissive.x == doctest::Approx(1));
    CHECK(emissive.y == doctest::Approx(1));
    CHECK(emissive.z == doctest::Approx(1));
}

TEST_CASE("It is possible to set the shininess to the material data") {
    auto data = MaterialData{};
    data.setShininess(1.0f);
    const auto shininess = data.getShininess();
    CHECK(shininess == doctest::Approx(1));
}

TEST_CASE("Material data string representation") {
    std::stringstream ss;
    ss << MaterialData{};
    CHECK(ss.str() == "Material(Ambient(0, 0, 0), Specular(0, 0, 0), Diffuse(0, 0, 0), Emissive(0, 0, 0), Shininess(0))");
}

}
