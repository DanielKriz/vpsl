#include <doctest/doctest.h>

#include <vp/interpreter/directive.hpp>

using namespace vp;

TEST_SUITE("Directives") {

TEST_CASE("just testing") {
    DirectiveBuilder builder{};
    Directive dir = builder
        .setDirectiveKind(DirectiveKind::Shader)
        .addClause(ClauseKind::Name)
        .addClause(ClauseKind::Type)
        .addClause(ClauseKind::Prepend)
        .addClause(ClauseKind::Append)
        .build();

    CHECK(dir.getDirectiveKind() == DirectiveKind::Shader);

    Directive another = Directive::create<DirectiveKind::Shader>();

    const std::vector<Token> tokens {
        {"", TokenKind::ShaderDirective, 0},
        {"", TokenKind::Type, 0},
        {"", TokenKind::LeftParen, 0},
        {"", TokenKind::Identifier, 0},
        {"", TokenKind::RightParen, 0},
    };

#if 0
    dir.areClausesCorrect(tokens);
    dir.populateClauses(tokens);
#endif
}

TEST_CASE("It is possible to instantiate a builder") {
    CHECK_NOTHROW(DirectiveBuilder{});
}

TEST_CASE("Building a directive with builder") {
    auto builder = DirectiveBuilder{};
    const Directive directive = builder.build();
    CHECK(std::is_same_v<decltype(directive), const Directive>);
}

}
