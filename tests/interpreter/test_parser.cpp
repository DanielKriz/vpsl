#include <vp/interpreter/parser.hpp>

#include <doctest/doctest.h>

using namespace vp;


TEST_SUITE("Parser") {

TEST_CASE("It is possible to create a parser") {
    CHECK_NOTHROW(Parser{});
}

TEST_CASE("The initial scope of the parser is global scope") {
    auto parser = Parser{};
    CHECK(parser.peekScope() == ParserScope::Global);
}

TEST_CASE("It is possible to push global shader scope from global scope") {
    auto parser = Parser{};
    parser.pushGlobalShaderScope();
    CHECK(parser.peekScope() == ParserScope::GlobalShader);
}

TEST_CASE("Pop from global shader scope results in global scope") {
    auto parser = Parser{};
    parser.pushGlobalShaderScope();
    CHECK(parser.peekScope() != ParserScope::Global);
    parser.popScope();
    CHECK(parser.peekScope() == ParserScope::Global);
}

TEST_CASE("Pushing global shader scope from other scope then globals results in an error") {
    auto parser = Parser{};
    SUBCASE("from program scope") {
        parser.pushScope();
        CHECK_THROWS(parser.pushGlobalShaderScope());
    }
    SUBCASE("from shader scope") {
        parser.pushScope();
        parser.pushScope();
        CHECK_THROWS(parser.pushGlobalShaderScope());
    }
}

TEST_CASE("After the first push the scope is program scope") {
    auto parser = Parser{};
    parser.pushScope();
    CHECK(parser.peekScope() == ParserScope::Program);
}

TEST_CASE("After the second push the scope is shader scope") {
    auto parser = Parser{};
    parser.pushScope();
    parser.pushScope();
    CHECK(parser.peekScope() == ParserScope::Shader);
}

TEST_CASE("it is not possible to have third push of the scope") {
    auto parser = Parser{};
    parser.pushScope();
    parser.pushScope();
    CHECK_THROWS(parser.pushScope());
}

TEST_CASE("After the pop from program scope the scope is global again") {
    auto parser = Parser{};
    parser.pushScope();
    parser.popScope();
    CHECK(parser.peekScope() == ParserScope::Global);
}

TEST_CASE("After the pop from shader scope the scope is program scope again") {
    auto parser = Parser{};
    parser.pushScope();
    parser.pushScope();
    parser.popScope();
    CHECK(parser.peekScope() == ParserScope::Program);
}

TEST_CASE("It is not possible to pop from global scope") {
    auto parser = Parser{};
    CHECK_THROWS(parser.popScope());
}

TEST_CASE("Parser can create directives from tokens") {
    SUBCASE("Shader Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::ShaderDirective, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::Shader);
    }
    SUBCASE("Program Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::ProgramDirective, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::Program);
    }
    SUBCASE("Begin Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::BeginDirective, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::Begin);
    }
    SUBCASE("End Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::EndDirective, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::End);
    }
    SUBCASE("Load Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::LoadDirective, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::Load);
    }
    SUBCASE("Texture Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::Texture, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::Texture);
    }
    SUBCASE("ResourceStore Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::ResourceStoreDirective, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::ResourceStore);
    }
    SUBCASE("FrameBuffer Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::FrameBufferDirective, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::FrameBuffer);
    }
    SUBCASE("Include Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::IncludeDirective, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::Include);
    }
    SUBCASE("CopyIn Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::CopyInDirective, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::CopyIn);
    }
    SUBCASE("Option Directive") {
        auto dir = Parser::createDirectiveFromToken(Token("", TokenKind::OptionDirective, 0));
        CHECK(dir->getDirectiveKind() == DirectiveKind::Option);
    }
}

TEST_CASE("Parser does not create directives for wrong tokens") {
    using enum TokenKind;
    const std::vector<TokenKind> kinds = {
        Unknown,
        LeftBracket,
        RightBracket,
        LeftParen,
        RightParen,
        Comma,
        Pragma,
        Namespace,
        Identifier,
        Type,
        Name,
        Append,
        Prepend,
        Pre,
        Post,
        Shaders,
        Format,
        Mesh,
        Material,
        Texture,
        SourceLine,

    };
    for (const auto kind : kinds) {
        auto dir = Parser::createDirectiveFromToken(Token("", kind, 0));
        CHECK_FALSE(dir.has_value());
    }
}

}
