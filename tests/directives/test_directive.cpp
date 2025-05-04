#include "vp/graphics/shader.hpp"
#include "vp/interpreter/lexer.hpp"
#include <doctest/doctest.h>

#include <vp/interpreter/directives/directive.hpp>

using namespace vp;

TEST_SUITE("Directives") {

TEST_CASE("Shader Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::Shader>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::Shader);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.size() == 4);
    CHECK(clauses.contains(ClauseKind::Name));
    CHECK(clauses.contains(ClauseKind::Type));
    CHECK(clauses.contains(ClauseKind::Prepend));
    CHECK(clauses.contains(ClauseKind::Append));
}

TEST_CASE("Directives throw an error on wrong input") {
    Lexer lex;
    SUBCASE("On duplicit clauses") {
        const auto tokens = lex.scan("#pragma vp shader name(sh1) name(sh2)");
        Directive dir = Directive::create<DirectiveKind::Shader>();
        CHECK_THROWS(dir.populateClauses(*tokens));
    }
    SUBCASE("On unsupported clauses") {
        const auto tokens = lex.scan("#pragma vp shader pre()");
        Directive dir = Directive::create<DirectiveKind::Shader>();
        CHECK_THROWS(dir.populateClauses(*tokens));
    }
    SUBCASE("On ill-formed clauses") {
        const auto tokens = lex.scan("#pragma vp shader name(sh1,sh2");
        Directive dir = Directive::create<DirectiveKind::Shader>();
        CHECK_THROWS(dir.populateClauses(*tokens));
    }
}

TEST_CASE("Shader Directive is possible to populate with valid input") {
    Lexer lex;
    const auto tokens = lex.scan("#pragma vp shader name(sh1) type(vertex) prepend(A, B) append(C, D)");
    Directive dir = Directive::create<DirectiveKind::Shader>();
    dir.populateClauses(*tokens);

    SUBCASE("it is possible to retrieve name") {
        const auto nameValue = dir.getParameter<ClauseKind::Name>();
        CHECK(nameValue.has_value());
        CHECK(nameValue.value() == "sh1");
    }

    SUBCASE("it is possible to retrieve type") {
        const auto typeValue = dir.getParameter<ClauseKind::Type>();
        CHECK(typeValue.has_value());
        CHECK(typeValue.value() == "vertex");
    }

    SUBCASE("it is possible to retrieve prepend") {
        const std::optional<std::vector<std::string>> prependValues = dir.getParameters<ClauseKind::Prepend>();
        CHECK(prependValues.has_value());
        CHECK((*prependValues)[0] == "A");
        CHECK((*prependValues)[1] == "B");
    }

    SUBCASE("it is possible to retrieve append") {
        const auto appendValues = dir.getParameters<ClauseKind::Append>();
        CHECK(appendValues.has_value());
        CHECK((*appendValues)[0] == "C");
        CHECK((*appendValues)[1] == "D");
    }
}

TEST_CASE("Shader Directive can provide shader kind") {
    Lexer lex;
    const auto tokens = lex.scan("#pragma vp shader name(sh1) type(vertex)");
    Directive dir = Directive::create<DirectiveKind::Shader>();
    dir.populateClauses(*tokens);
    const auto type = dir.getParameter<gl::ShaderKind>();
    CHECK(type.has_value());
    CHECK(type.value() == gl::ShaderKind::Vertex);
}

TEST_CASE("Program Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::Program>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::Program);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.size() == 3);
    CHECK(clauses.contains(ClauseKind::Name));
    CHECK(clauses.contains(ClauseKind::Pre));
    CHECK(clauses.contains(ClauseKind::Post));
}

TEST_CASE("Begin Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::Begin>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::Begin);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.empty());
}

TEST_CASE("End Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::End>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::End);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.empty());
}

}
