#include <doctest/doctest.h>

#include <vp/interpreter/token.hpp>
#include <vp/interpreter/token_kind.hpp>

using namespace vp;

TEST_SUITE("Token") {

TEST_CASE("Simple default constructor") {
    CHECK_NOTHROW(Token());
}

TEST_CASE("Partial constructor") {
    auto kind = TokenKind::Draw;
    CHECK_NOTHROW(Token{kind});
}

TEST_CASE("Fully defined constructor") {
    CHECK_NOTHROW(Token("", TokenKind::Draw, 0));
}

TEST_CASE("it is possible to get the lexeme out of token") {
    auto token = Token("draw", TokenKind::Draw, 42);
    CHECK(token.getLexeme() == "draw");
}

TEST_CASE("it is possible to get the kind out of token") {
    auto token = Token("draw", TokenKind::Draw, 42);
    CHECK(token.getTokenKind() == TokenKind::Draw);
}

TEST_CASE("it is possible to get the line number out of token") {
    auto token = Token("draw", TokenKind::Draw, 42);
    CHECK(token.getLineNumber() == 42);
}

TEST_CASE("Token fmt compatibility") {
    auto token = Token("draw", TokenKind::Draw, 42);
    CHECK(fmt::format("{}", token) == "Token(draw, Draw, 42)");
}

TEST_CASE("Token representation string") {
    auto token = Token("draw", TokenKind::Draw, 42);
    std::stringstream ss;
    ss << token;
    CHECK(ss.str() == "Token(draw, Draw, 42)");
}

}
