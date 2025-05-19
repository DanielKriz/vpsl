#include <doctest/doctest.h>

#include <vp/description/program_description.hpp>
#include <vp/description/buffer_description.hpp>
#include <vp/description/frame_buffer_description.hpp>
#include <vp/description/shader_code.hpp>
#include <vp/resources/material_data.hpp>
#include <vp/resources/texture.hpp>
#include <vp/resources/mesh_description.hpp>

using namespace vp;
using namespace vp::desc;

TEST_SUITE("ProgramDescriptionBuilder") {

TEST_CASE("It is possible to initialize program description builder") {
    CHECK_NOTHROW(ProgramDescriptionBuilder{});
}

TEST_CASE("It is possible to build program description with the builder") {
    auto builder = ProgramDescriptionBuilder{};
    auto programDesc = builder.build();
    auto defaultOpts = Options{};
    CHECK(programDesc.getBufferDescriptions().empty());
    CHECK(programDesc.getTextures().empty());
    CHECK(programDesc.getMaterialDescriptions().empty());
    CHECK(programDesc.getShaderCodes().empty());
    CHECK(programDesc.getOptions() == defaultOpts);
    CHECK_FALSE(programDesc.hasFrameBuffer());
    CHECK_FALSE(programDesc.hasMesh());
}

TEST_CASE("Creating a shader name without program names throws") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_THROWS(std::ignore = builder.createShaderName("shader"));
}

TEST_CASE("Creating a shader name throws after fresh build") {
    auto builder = ProgramDescriptionBuilder{};
    builder.setName("main");
    CHECK_NOTHROW(std::ignore = builder.createShaderName("shader"));
    builder.build();
    CHECK_THROWS(std::ignore = builder.createShaderName("shader"));
}

TEST_CASE("Creating a shader name with normal program name") {
    auto builder = ProgramDescriptionBuilder{};
    builder.setName("main");
    CHECK(builder.createShaderName("shader") == "main:shader");
}

TEST_CASE("Creating a shader name with ID name") {
    auto builder = ProgramDescriptionBuilder{};
    builder.setNameFromID();
    CHECK(builder.createShaderName("shader") == "0:shader");
}

TEST_CASE("Adding textures") {
    auto builder = ProgramDescriptionBuilder{};
    SUBCASE("From Description") {
        auto desc = TextureDescription {};
        CHECK_NOTHROW(builder.addTexture(desc));
        auto programDesc = builder.build();
        CHECK(programDesc.getTextures()[0] == desc);
    }
    SUBCASE("From location and pointer") {
        Texture tex { nullptr };
        CHECK_NOTHROW(builder.addTexture(42, &tex));
        auto programDesc = builder.build();
        CHECK(programDesc.getTextures()[0].location == 42);
        CHECK(programDesc.getTextures()[0].pTexture == &tex);
    }
    SUBCASE("From location and reference") {
        Texture tex { nullptr };
        CHECK_NOTHROW(builder.addTexture(42, tex));
        auto programDesc = builder.build();
        CHECK(programDesc.getTextures()[0].location == 42);
        CHECK(programDesc.getTextures()[0].pTexture == &tex);
    }
}

TEST_CASE("Adding Materials") {
    auto builder = ProgramDescriptionBuilder{};
    auto desc = MaterialData{};
    CHECK_NOTHROW(builder.addMaterial(desc));
    auto programDesc = builder.build();
    CHECK(programDesc.getMaterialDescriptions()[0] == &desc);
}

TEST_CASE("Adding Buffers") {
    auto builder = ProgramDescriptionBuilder{};
    auto desc = BufferDescription{1, 1};
    CHECK_NOTHROW(builder.addBuffer(desc));
    auto programDesc = builder.build();
    CHECK(programDesc.getBufferDescriptions()[0] == &desc);
}

TEST_CASE("Adding Shader Codes") {
    auto builder = ProgramDescriptionBuilder{};
    auto code = ShaderCode{};
    CHECK_NOTHROW(builder.addShaderCode(code));
    auto programDesc = builder.build();
    CHECK(programDesc.getShaderCodes()[0] == &code);
}

TEST_CASE("Setting of a mesh") {
    auto builder = ProgramDescriptionBuilder{};
    auto desc = MeshDescription{};
    CHECK_NOTHROW(builder.setMesh(desc));
    auto programDesc = builder.build();
    // TODO: add some meaningfull check
}

TEST_CASE("Setting of a frame buffer") {
    auto builder = ProgramDescriptionBuilder{};
    auto desc = FrameBufferDescription{};
    CHECK_NOTHROW(builder.setFrameBuffer(desc));
    auto programDesc = builder.build();
    // TODO: add some meaningfull check
}

}
