#include <doctest/doctest.h>

#include <vp/description/program_description.hpp>

using namespace vp::desc;

TEST_SUITE("Program Description") {

TEST_CASE("Simple construction does not throw") {
    CHECK_NOTHROW(ProgramDescription{});
}

TEST_CASE("It has copy constructor") {
    const auto desc = ProgramDescription{};
    CHECK_NOTHROW(ProgramDescription{desc});
}

TEST_CASE("It has move constructor") {
    auto desc = ProgramDescription{};
    CHECK_NOTHROW(ProgramDescription{std::move(desc)});
}

TEST_CASE("It does support copy assignment") {
    const auto desc = ProgramDescription{};
    ProgramDescription other = desc;
    CHECK(desc.getName() == other.getName());
    CHECK(desc.getOptions() == other.getOptions());
    // Other attributes are empty
}

TEST_CASE("It does support move assignment") {
    auto desc = ProgramDescription{};
    auto &&rdesc = std::move(desc);
    ProgramDescription other = rdesc;
    CHECK(desc.getName().empty());
    const auto defaultOpts = vp::Options{};
    CHECK(desc.getOptions() == defaultOpts);
}

TEST_CASE("After construction the name attribute is empty") {
    const auto desc = ProgramDescription{};
    CHECK(desc.getName().empty());
}

TEST_CASE("After construction the textures attribute is empty") {
    const auto desc = ProgramDescription{};
    CHECK(desc.getTextures().empty());
}

TEST_CASE("After construction the materials attribute is empty") {
    const auto desc = ProgramDescription{};
    CHECK(desc.getMaterialDescriptions().empty());
}

TEST_CASE("After construction the buffers attribute is empty") {
    const auto desc = ProgramDescription{};
    CHECK(desc.getBufferDescriptions().empty());
}

TEST_CASE("After construction the shader codes attribute is empty") {
    const auto desc = ProgramDescription{};
    CHECK(desc.getShaderCodes().empty());
}

TEST_CASE("After construction the options attribute is default") {
    const auto desc = ProgramDescription{};
    CHECK(desc.getOptions() == vp::Options{});
}

TEST_CASE("After construction it does not have frame buffer") {
    const auto desc = ProgramDescription{};
    CHECK_FALSE(desc.hasFrameBuffer());
}

TEST_CASE("After construction it does not have mesh") {
    const auto desc = ProgramDescription{};
    CHECK_FALSE(desc.hasMesh());
}

TEST_CASE("Getting the mesh after construction does throw") {
    const auto desc = ProgramDescription{};
    CHECK_THROWS(std::ignore = desc.getMeshDescription());
}

TEST_CASE("Getting the frame buffer after construction does throw") {
    const auto desc = ProgramDescription{};
    CHECK_THROWS(std::ignore = desc.getFrameBufferDescription());
}

TEST_CASE("Getting the mesh after construction does throw") {
    const auto desc = ProgramDescription{};
    CHECK_THROWS(std::ignore = desc.getMeshDescription());
}

}
