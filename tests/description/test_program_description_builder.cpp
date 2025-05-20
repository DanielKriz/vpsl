#include <doctest/doctest.h>

#include <vp/description/buffer_description.hpp>
#include <vp/description/frame_buffer_description.hpp>
#include <vp/description/program_description.hpp>
#include <vp/description/shader_code.hpp>
#include <vp/resources/material_data.hpp>
#include <vp/resources/mesh_data.hpp>
#include <vp/resources/texture.hpp>

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
    CHECK_FALSE(programDesc.hasDrawCommand());
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
    auto desc = MeshData{};
    CHECK_NOTHROW(builder.setMesh(desc));
    auto programDesc = builder.build();
    CHECK(programDesc.hasMesh());
    CHECK_NOTHROW(std::ignore = programDesc.getMeshDescription());
}

TEST_CASE("Setting a draw command") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.setDrawCommand(DrawMode::Lines, 42));
    auto programDesc = builder.build();
    auto cmd = programDesc.getDrawCommand();
    CHECK(cmd.mode == DrawMode::Lines);
    CHECK(cmd.count == 42);
}

TEST_CASE("Setting of a frame buffer") {
    auto builder = ProgramDescriptionBuilder{};
    auto desc = FrameBufferDescription{};
    CHECK_NOTHROW(builder.setFrameBuffer(desc));
    auto programDesc = builder.build();
    CHECK(programDesc.hasFrameBuffer());
    CHECK_NOTHROW(std::ignore = programDesc.getFrameBufferDescription());
}

TEST_CASE("It is not possible to add attributes to a program that does not have a mesh assigned") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_THROWS(builder.addAttributeToMesh(AttributeType::Position, 0));
}

TEST_CASE("Setting mesh attribute") {
    auto builder = ProgramDescriptionBuilder{};
    auto desc = MeshData{};
    builder.setMesh(desc);
    CHECK_NOTHROW(builder.addAttributeToMesh(AttributeType::Position, 42));
    auto programDesc = builder.build();

    const auto &mesh = programDesc.getMeshDescription();
    const auto &attrs = mesh.getAttributeDescription();
    CHECK(attrs.getAttributes()[0].type == AttributeType::Position);
    CHECK(attrs.getAttributes()[0].location == 42);
}

TEST_CASE("Setting options") {
    auto builder = ProgramDescriptionBuilder{};
    auto opts = Options{};
    opts.isBlendingEnabled = true;
    CHECK_NOTHROW(builder.setOptions(opts));
    auto desc = builder.build();
    CHECK(desc.getOptions().isBlendingEnabled == true);
}

TEST_CASE("Setting polygon mode") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.setOption(gl::PolygonMode::Fill));
    auto desc = builder.build();
    CHECK(desc.getOptions().frontFacePolygonMode == gl::PolygonMode::Fill);
    CHECK(desc.getOptions().backFacePolygonMode == gl::PolygonMode::Fill);
}

TEST_CASE("Setting front face polygon mode") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.setOption(gl::Face::Front, gl::PolygonMode::Point));
    auto desc = builder.build();
    CHECK(desc.getOptions().frontFacePolygonMode == gl::PolygonMode::Point);
    CHECK(desc.getOptions().backFacePolygonMode == gl::PolygonMode::Fill);
}

TEST_CASE("Setting back face polygon mode") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.setOption(gl::Face::Back, gl::PolygonMode::Point));
    auto desc = builder.build();
    CHECK(desc.getOptions().frontFacePolygonMode == gl::PolygonMode::Fill);
    CHECK(desc.getOptions().backFacePolygonMode == gl::PolygonMode::Point);
}

TEST_CASE("Setting culling mode") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.setOption(gl::CullingMode::Front));
    auto desc = builder.build();
    CHECK(desc.getOptions().cullingMode == gl::CullingMode::Front);
}

TEST_CASE("Setting culling mode") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.setOption(gl::FrontFaceMode::CW));
    auto desc = builder.build();
    CHECK(desc.getOptions().frontFaceMode == gl::FrontFaceMode::CW);
}

TEST_CASE("Setting source blending factor") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.setOption(gl::BlendingFactor::SourceColor, true));
    auto desc = builder.build();
    CHECK(desc.getOptions().srcBlendFactor == gl::BlendingFactor::SourceColor);
    CHECK(desc.getOptions().dstBlendFactor == gl::BlendingFactor::Zero);
}


TEST_CASE("Setting source blending factor") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.setOption(gl::BlendingFactor::SourceColor, false));
    auto desc = builder.build();
    CHECK(desc.getOptions().srcBlendFactor == gl::BlendingFactor::One);
    CHECK(desc.getOptions().dstBlendFactor == gl::BlendingFactor::SourceColor);
}

TEST_CASE("Setting the Depth function") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.setOption(gl::DepthFunction::Never));
    auto desc = builder.build();
    CHECK(desc.getOptions().depthFunction == gl::DepthFunction::Never);
}

TEST_CASE("Setting the enabling depth test") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.enableDepthTest(true));
    auto desc = builder.build();
    CHECK(desc.getOptions().isDepthTestEnabled == true);
}

TEST_CASE("Setting the enabling blending") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.enableBlending(true));
    auto desc = builder.build();
    CHECK(desc.getOptions().isBlendingEnabled == true);
}

TEST_CASE("Setting the enabling face culling") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.enableFaceCulling(true));
    auto desc = builder.build();
    CHECK(desc.getOptions().isFaceCullingEnabled == true);
}

TEST_CASE("Resetting the builder") {
    auto builder = ProgramDescriptionBuilder{};
    CHECK_NOTHROW(builder.reset());
}

}
