#include <doctest/doctest.h>

#include <vp/interpreter/directive.hpp>

using namespace vp;

TEST_SUITE("Directives") {

TEST_CASE("just testing") {
    DirectiveBuilder builder{};
    Directive dir = builder
        .setDirectiveKind(DirectiveKind::Shader)
        .setDirectiveToken(TokenKind::ShaderDirective)
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

}
