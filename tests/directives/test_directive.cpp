#include "vp/description/shader_code.hpp"
#include "vp/interpreter/lexer.hpp"
#include <doctest/doctest.h>

#include <vp/interpreter/directive.hpp>

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

TEST_CASE("Requested clauses that are not populated do not return a value") {
    Lexer lex;
    const auto tokens = lex.scan("#pragma vp shader name(sh1) type(vertex) prepend(A, B) append(C, D)");
    Directive dir = Directive::create<DirectiveKind::Shader>();
    CHECK_FALSE(dir.getParameter<ClauseKind::Name>().has_value());
    CHECK_FALSE(dir.getParameter<ClauseKind::Type>().has_value());
    CHECK_FALSE(dir.getParameters<ClauseKind::Prepend>().has_value());
    CHECK_FALSE(dir.getParameters<ClauseKind::Append>().has_value());
}

TEST_CASE("Requested clauses that are not present do not return a value") {
    Lexer lex;
    const auto tokens = lex.scan("#pragma vp shader");
    Directive dir = Directive::create<DirectiveKind::Shader>();
    CHECK_FALSE(dir.getParameter<ClauseKind::Name>().has_value());
    CHECK_FALSE(dir.getParameter<ClauseKind::Type>().has_value());
    CHECK_FALSE(dir.getParameters<ClauseKind::Prepend>().has_value());
    CHECK_FALSE(dir.getParameters<ClauseKind::Append>().has_value());
}

TEST_CASE("Requested clauses that are not present do not return a value even after populate") {
    Lexer lex;
    const auto tokens = lex.scan("#pragma vp shader").value();
    Directive dir = Directive::create<DirectiveKind::Shader>();
    dir.populateClauses(tokens);
    CHECK_FALSE(dir.getParameter<ClauseKind::Name>().has_value());
    CHECK_FALSE(dir.getParameter<ClauseKind::Type>().has_value());
    CHECK_FALSE(dir.getParameters<ClauseKind::Prepend>().has_value());
    CHECK_FALSE(dir.getParameters<ClauseKind::Append>().has_value());
}

TEST_CASE("It is possible to call getParameter on multiple parameter clauses and vice versa") {
    Lexer lex;
    const auto tokens = lex.scan("#pragma vp shader name(sh1) type(vertex) prepend(A, B) append(C, D)");
    Directive dir = Directive::create<DirectiveKind::Shader>();
    dir.populateClauses(*tokens);
    CHECK(dir.getParameters<ClauseKind::Name>().value()[0] == "sh1");
    CHECK(dir.getParameters<ClauseKind::Type>().value()[0] == "vertex");
    CHECK(dir.getParameter<ClauseKind::Prepend>().value() == "A");
    CHECK(dir.getParameter<ClauseKind::Append>().value() == "C");
}

TEST_CASE("Shader Directive can provide shader kind") {
    Lexer lex;
    const auto tokens = lex.scan("#pragma vp shader name(sh1) type(vertex)");
    Directive dir = Directive::create<DirectiveKind::Shader>();
    dir.populateClauses(*tokens);
    const auto type = dir.getParameter<ShaderCodeKind>();
    CHECK(type.has_value());
    CHECK(type.value() == ShaderCodeKind::Vertex);
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
