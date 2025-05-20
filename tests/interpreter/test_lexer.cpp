#include <doctest/doctest.h>

#include <string>
#include <vp/interpreter/lexer.hpp>
#include <vp/utils.hpp>

using namespace vp;

TEST_SUITE("Lexer") {

TEST_CASE("it is possible to create an empty lexer") {
    CHECK_NOTHROW(Lexer());
}

TEST_CASE("checking whether line is a directive") {
    SUBCASE("with a valid line") {
        const std::string line = "#pragma vp something something";
        CHECK(Lexer::isDirective(line) == true);
    }
    SUBCASE("line with additional white space") {
        SUBCASE("Prefix") {
            const std::string line = "     #pragma vp something";
            CHECK(Lexer::isDirective(line) == true);
        }
        SUBCASE("Infix") {
            const std::string line = "#pragma       vp something";
            CHECK(Lexer::isDirective(line) == true);
        }
        SUBCASE("Postfix") {
            const std::string line = "#pragma vp         something";
            CHECK(Lexer::isDirective(line) == true);
        }
    }
    SUBCASE("with an invalid line") {
        const std::string line = "simply wrong";
        CHECK(Lexer::isDirective(line) == false);
    }
    SUBCASE("with an empty line") {
        const std::string line{};
        CHECK(Lexer::isDirective(line) == false);
    }
}

TEST_CASE("Lexer is able to check whether the line is continuous") {
    SUBCASE("with a valid line") {
        const std::string line = "#pragma vp something something \\";
        CHECK(Lexer::isContinuous(line) == true);
    }
    SUBCASE("line with additional white space") {
        SUBCASE("Prefix") {
            const std::string line = "     #pragma vp \\";
            CHECK(Lexer::isContinuous(line) == true);
        }
        SUBCASE("Infix") {
            const std::string line = "#pragma vp       \\";
            CHECK(Lexer::isContinuous(line) == true);
        }
        SUBCASE("Postfix") {
            const std::string line = "#pragma vp \\         ";
            CHECK(Lexer::isContinuous(line) == true);
        }
    }
    SUBCASE("with an invalid line") {
        const std::string line = "simply wrong";
        CHECK(Lexer::isContinuous(line) == false);
    }
    SUBCASE("with an empty line") {
        const std::string line{};
        CHECK(Lexer::isContinuous(line) == false);
    }
}

TEST_CASE("It should be possible to join lines") {
    std::string dstLine = "#pragma vp something \\";
    const std::string srcLine = "other(values)";
    const std::string dstLineCopy = dstLine;

    Lexer::joinLines(dstLine, srcLine);
    CHECK(dstLine == "#pragma vp something other(values)");
    REQUIRE(dstLine != dstLineCopy);
}

TEST_CASE("It should be possible to join lines with whitespace") {
    std::string dstLine = "     #pragma     vp something     \\     \n";
    const std::string srcLine = "     other(values)    \n";
    const std::string dstLineCopy = dstLine;

    Lexer::joinLines(dstLine, srcLine);
    CHECK(dstLine == "#pragma     vp something other(values)");
    REQUIRE(dstLine != dstLineCopy);
}

TEST_CASE("it should be possible to tokenize all keywords") {
    const Lexer lexer{};
    SUBCASE("program") {
        CHECK(lexer.mapTokenKind("program") == TokenKind::ProgramDirective);
    }
    SUBCASE("shader") {
        CHECK(lexer.mapTokenKind("shader") == TokenKind::ShaderDirective);
    }
    SUBCASE("texture") {
        CHECK(lexer.mapTokenKind("texture") == TokenKind::Texture);
    }
    SUBCASE("copyin") {
        CHECK(lexer.mapTokenKind("copyin") == TokenKind::CopyInDirective);
    }
    SUBCASE("begin") {
        CHECK(lexer.mapTokenKind("begin") == TokenKind::BeginDirective);
    }
    SUBCASE("end") {
        CHECK(lexer.mapTokenKind("end") == TokenKind::EndDirective);
    }
    SUBCASE("include") {
        CHECK(lexer.mapTokenKind("include") == TokenKind::IncludeDirective);
    }
    SUBCASE("namespace") {
        CHECK(lexer.mapTokenKind("vp") == TokenKind::Namespace);
    }
    SUBCASE("pragma") {
        CHECK(lexer.mapTokenKind("#pragma") == TokenKind::Pragma);
    }
    SUBCASE("option") {
        CHECK(lexer.mapTokenKind("option") == TokenKind::OptionDirective);
    }
    SUBCASE("name") {
        CHECK(lexer.mapTokenKind("name") == TokenKind::Name);
    }
    SUBCASE("type") {
        CHECK(lexer.mapTokenKind("type") == TokenKind::Type);
    }
    SUBCASE("pre") {
        CHECK(lexer.mapTokenKind("pre") == TokenKind::Pre);
    }
    SUBCASE("post") {
        CHECK(lexer.mapTokenKind("post") == TokenKind::Post);
    }
    SUBCASE("append") {
        CHECK(lexer.mapTokenKind("append") == TokenKind::Append);
    }
    SUBCASE("prepend") {
        CHECK(lexer.mapTokenKind("prepend") == TokenKind::Prepend);
    }
    SUBCASE("format") {
        CHECK(lexer.mapTokenKind("format") == TokenKind::Format);
    }
    SUBCASE("framebuffer") {
        CHECK(lexer.mapTokenKind("framebuffer") == TokenKind::FrameBufferDirective);
    }
    SUBCASE("mesh") {
        CHECK(lexer.mapTokenKind("mesh") == TokenKind::Mesh);
    }
    SUBCASE("load") {
        CHECK(lexer.mapTokenKind("load") == TokenKind::LoadDirective);
    }
    SUBCASE("material") {
        CHECK(lexer.mapTokenKind("material") == TokenKind::Material);
    }
}

TEST_CASE("The pragma and namespace do not contribute to the stream of tokens") {
    auto lexer = Lexer{};

    auto tokens = lexer.scan("#pragma vp begin");
    CHECK(tokens->size() == 1);
}

TEST_CASE("Lexer ignore tokens after the //") {
    auto lexer = Lexer{};

    auto tokens = lexer.scan("#pragma vp begin // begin begin");
    CHECK(tokens->size() == 1);
}

TEST_CASE("Lexing an empty line returns empty token stream") {
    auto lexer = Lexer{};
    auto tokens = lexer.scan("");
    CHECK_FALSE(tokens.has_value());
}

}
