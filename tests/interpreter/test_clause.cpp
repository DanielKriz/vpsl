#include <vector>

#include <doctest/doctest.h>

#include <vp/interpreter/clause.hpp>
#include <vp/interpreter/token.hpp>

using namespace vp;

TEST_SUITE("Clause") {

TEST_CASE("Simple Matching") {
    std::vector<Token> tokens = {
        Token { "A", TokenKind::Name, 0},
        Token { "B", TokenKind::LeftParen, 0},
        Token { "C", TokenKind::Identifier, 0},
        Token { "D", TokenKind::RightParen, 0},
    };

    NameClause cls;
    CHECK(cls.isValidClause(tokens));
}

TEST_CASE("Simple wrong Matching") {
    std::vector<Token> tokens = {
        Token { "A", TokenKind::Name, 0},
        Token { "B", TokenKind::LeftParen, 0},
        Token { "C", TokenKind::Identifier, 0},
        Token { "E", TokenKind::Comma, 0},
        Token { "F", TokenKind::RightParen, 0},
    };

    NameClause cls;
    CHECK_FALSE(cls.isValidClause(tokens));
}

TEST_CASE("Simple Missing Matching") {
    std::vector<Token> tokens = {
        Token { "A", TokenKind::Name, 0},
        Token { "B", TokenKind::LeftParen, 0},
        Token { "C", TokenKind::RightParen, 0},
    };

    NameClause cls;
    CHECK_FALSE(cls.isValidClause(tokens));
}

}
