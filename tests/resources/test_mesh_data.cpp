#include <vp/resources/mesh_data.hpp>

#include <doctest/doctest.h>

using namespace vp;

TEST_SUITE("Mesh Data") {

TEST_CASE("Simple Constructor") {
    std::vector<gl::Vertex> vertices;
    vertices.emplace_back();

    CHECK_NOTHROW(MeshData{vertices});
}

TEST_CASE("It is possible to get vertices from the mesh") {
    std::vector<gl::Vertex> vertices;
    vertices.emplace_back();
    auto data = MeshData{vertices};
    const auto &assigned = data.getVertices();
    CHECK(assigned.begin()->position.x == doctest::Approx(0));
}

TEST_CASE("It is possible to assign vertices to mesh") {
    std::vector<gl::Vertex> vertices;
    vertices.emplace_back();
    auto data = MeshData{vertices};
    std::vector<gl::Vertex> newVertices;
    newVertices.emplace_back();
    newVertices.back().position.x = 1.0f;
    data.setVertices(newVertices);
    const auto &assigned = data.getVertices();
    CHECK(assigned.begin()->position.x == doctest::Approx(1));
}

TEST_CASE("Getting the count of vertices from mesh") {
    std::vector<gl::Vertex> vertices;
    vertices.emplace_back();
    auto data = MeshData{vertices};
    CHECK(data.getVertexCount() == 1);
}

}
