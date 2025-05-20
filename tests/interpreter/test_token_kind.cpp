#include <doctest/doctest.h>

#include <vp/interpreter/token_kind.hpp>

using namespace vp;

TEST_SUITE("Token Kind") {

TEST_CASE("String representation of unknown") {
    std::stringstream ss;
    ss << TokenKind::Unknown;
    CHECK(ss.str() == "Unknown");
}

TEST_CASE("String representation of LeftBracket") {
    std::stringstream ss;
    ss << TokenKind::LeftBracket;
    CHECK(ss.str() == "LeftBracket");
}

TEST_CASE("String representation of RightBracket") {
    std::stringstream ss;
    ss << TokenKind::RightBracket;
    CHECK(ss.str() == "RightBracket");
}

TEST_CASE("String representation of LeftParen") {
    std::stringstream ss;
    ss << TokenKind::LeftParen;
    CHECK(ss.str() == "LeftParen");
}

TEST_CASE("String representation of RightParen") {
    std::stringstream ss;
    ss << TokenKind::RightParen;
    CHECK(ss.str() == "RightParen");
}

TEST_CASE("String representation of Comma") {
    std::stringstream ss;
    ss << TokenKind::Comma;
    CHECK(ss.str() == "Comma");
}

TEST_CASE("String representation of Pragma") {
    std::stringstream ss;
    ss << TokenKind::Pragma;
    CHECK(ss.str() == "Pragma");
}

TEST_CASE("String representation of Namespace") {
    std::stringstream ss;
    ss << TokenKind::Namespace;
    CHECK(ss.str() == "Namespace");
}

TEST_CASE("String representation of Identifier") {
    std::stringstream ss;
    ss << TokenKind::Identifier;
    CHECK(ss.str() == "Identifier");
}

TEST_CASE("String representation of ShaderDirective") {
    std::stringstream ss;
    ss << TokenKind::ShaderDirective;
    CHECK(ss.str() == "ShaderDirective");
}

TEST_CASE("String representation of Type") {
    std::stringstream ss;
    ss << TokenKind::Type;
    CHECK(ss.str() == "Type");
}

TEST_CASE("String representation of Name") {
    std::stringstream ss;
    ss << TokenKind::Name;
    CHECK(ss.str() == "Name");
}

TEST_CASE("String representation of Append") {
    std::stringstream ss;
    ss << TokenKind::Append;
    CHECK(ss.str() == "Append");
}

TEST_CASE("String representation of Prepend") {
    std::stringstream ss;
    ss << TokenKind::Prepend;
    CHECK(ss.str() == "Prepend");
}

TEST_CASE("String representation of ProgramDirective") {
    std::stringstream ss;
    ss << TokenKind::ProgramDirective;
    CHECK(ss.str() == "ProgramDirective");
}

TEST_CASE("String representation of Pre") {
    std::stringstream ss;
    ss << TokenKind::Pre;
    CHECK(ss.str() == "Pre");
}

TEST_CASE("String representation of Post") {
    std::stringstream ss;
    ss << TokenKind::Post;
    CHECK(ss.str() == "Post");
}

TEST_CASE("String representation of Shaders") {
    std::stringstream ss;
    ss << TokenKind::Shaders;
    CHECK(ss.str() == "Shaders");
}

TEST_CASE("String representation of Draw") {
    std::stringstream ss;
    ss << TokenKind::Draw;
    CHECK(ss.str() == "Draw");
}

TEST_CASE("String representation of IncludeDirective") {
    std::stringstream ss;
    ss << TokenKind::IncludeDirective;
    CHECK(ss.str() == "IncludeDirective");
}

TEST_CASE("String representation of Path") {
    std::stringstream ss;
    ss << TokenKind::Path;
    CHECK(ss.str() == "Path");
}

TEST_CASE("String representation of OptionDirective") {
    std::stringstream ss;
    ss << TokenKind::OptionDirective;
    CHECK(ss.str() == "OptionDirective");
}

TEST_CASE("String representation of Enable") {
    std::stringstream ss;
    ss << TokenKind::Enable;
    CHECK(ss.str() == "Enable");
}

TEST_CASE("String representation of Persistent") {
    std::stringstream ss;
    ss << TokenKind::Persistent;
    CHECK(ss.str() == "Persistent");
}

TEST_CASE("String representation of Value") {
    std::stringstream ss;
    ss << TokenKind::Value;
    CHECK(ss.str() == "Value");
}

TEST_CASE("String representation of Format") {
    std::stringstream ss;
    ss << TokenKind::Format;
    CHECK(ss.str() == "Format");
}

TEST_CASE("String representation of LoadDirective") {
    std::stringstream ss;
    ss << TokenKind::LoadDirective;
    CHECK(ss.str() == "LoadDirective");
}

TEST_CASE("String representation of Mesh") {
    std::stringstream ss;
    ss << TokenKind::Mesh;
    CHECK(ss.str() == "Mesh");
}

TEST_CASE("String representation of Material") {
    std::stringstream ss;
    ss << TokenKind::Material;
    CHECK(ss.str() == "Material");
}

TEST_CASE("String representation of Texture") {
    std::stringstream ss;
    ss << TokenKind::Texture;
    CHECK(ss.str() == "Texture");
}

TEST_CASE("String representation of FrameBufferDirective") {
    std::stringstream ss;
    ss << TokenKind::FrameBufferDirective;
    CHECK(ss.str() == "FrameBufferDirective");
}

TEST_CASE("String representation of CopyInDirective") {
    std::stringstream ss;
    ss << TokenKind::CopyInDirective;
    CHECK(ss.str() == "CopyInDirective");
}

TEST_CASE("String representation of BeginDirective") {
    std::stringstream ss;
    ss << TokenKind::BeginDirective;
    CHECK(ss.str() == "BeginDirective");
}

TEST_CASE("String representation of EndDirective") {
    std::stringstream ss;
    ss << TokenKind::EndDirective;
    CHECK(ss.str() == "EndDirective");
}

TEST_CASE("String representation of ResourceStoreDirective") {
    std::stringstream ss;
    ss << TokenKind::ResourceStoreDirective;
    CHECK(ss.str() == "ResourceStoreDirective");
}

TEST_CASE("String representation of SourceLine") {
    std::stringstream ss;
    ss << TokenKind::SourceLine;
    CHECK(ss.str() == "SourceLine");
}

TEST_CASE("Token kind fmt compatibility") {
    CHECK(fmt::format("{}", TokenKind::Draw) == "Draw");
}

}
