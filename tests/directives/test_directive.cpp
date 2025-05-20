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

TEST_CASE("Program Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::Program>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::Program);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.size() == 6);
    CHECK(clauses.contains(ClauseKind::Name));
    CHECK(clauses.contains(ClauseKind::Pre));
    CHECK(clauses.contains(ClauseKind::Post));
    CHECK(clauses.contains(ClauseKind::Shaders));
    CHECK(clauses.contains(ClauseKind::Mesh));
    CHECK(clauses.contains(ClauseKind::Draw));
    CHECK_FALSE(dir.hasSubCommand());
}

TEST_CASE("load Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::Begin>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::Begin);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.empty());
    CHECK(dir.hasSubCommand());
}

TEST_CASE("Load directive create method") {
    const Directive dir = Directive::create<DirectiveKind::Load>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::Load);

    CHECK(dir.hasSubCommand() == true);
    auto &cmds = dir.getSubCommandTokens();
    CHECK(cmds.contains(TokenKind::Texture));
    CHECK(cmds.contains(TokenKind::Mesh));
    CHECK(cmds.contains(TokenKind::Material));

    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.size() == 2);
    CHECK(clauses.contains(ClauseKind::Name));
    CHECK(clauses.contains(ClauseKind::Path));
}

TEST_CASE("Texture Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::Texture>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::Texture);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.size() == 1);
    CHECK(clauses.contains(ClauseKind::Name));
    CHECK_FALSE(dir.hasSubCommand());
}

TEST_CASE("Include Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::Include>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::Include);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.size() == 1);
    CHECK(clauses.contains(ClauseKind::Name));
    CHECK_FALSE(dir.hasSubCommand());
}

TEST_CASE("FrameBuffer Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::FrameBuffer>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::FrameBuffer);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.empty());
    CHECK_FALSE(dir.hasSubCommand());
}

TEST_CASE("CopyIn Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::CopyIn>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::CopyIn);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.size() == 2);
    CHECK(clauses.contains(ClauseKind::Name));
    CHECK(clauses.contains(ClauseKind::Value));
    CHECK_FALSE(dir.hasSubCommand());
}

TEST_CASE("Option Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::Option>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::Option);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.size() == 4);
    CHECK(clauses.contains(ClauseKind::Type));
    CHECK(clauses.contains(ClauseKind::Enable));
    CHECK(clauses.contains(ClauseKind::Value));
    CHECK(clauses.contains(ClauseKind::Persistent));
    CHECK_FALSE(dir.hasSubCommand());
}

TEST_CASE("Begin Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::Begin>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::Begin);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.empty());
    CHECK_FALSE(dir.hasSubCommand());
}

TEST_CASE("End Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::End>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::End);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.empty());
    CHECK_FALSE(dir.hasSubCommand());
}

TEST_CASE("By default the subcommand is an empty token") {
    Directive dir = DirectiveBuilder().build();
    CHECK(dir.getSubCommand() == TokenKind::Unknown);
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

TEST_CASE("Parameters of load texture clause") {
    Lexer lex;
    auto tokens = lex.scan("#pragma vp load texture name(A) path(some/path)");
    Directive dir = Directive::create<DirectiveKind::Load>();
    tokens->erase(tokens->begin());
    const auto clauseTokens = *tokens;
    dir.populateClauses(clauseTokens);
    CHECK(dir.getSubCommand() == TokenKind::Texture);
}

TEST_CASE("Parameters of load material clause") {
    Lexer lex;
    auto tokens = lex.scan("#pragma vp load material name(A) path(some/path)");
    Directive dir = Directive::create<DirectiveKind::Load>();
    tokens->erase(tokens->begin());
    const auto clauseTokens = *tokens;
    dir.populateClauses(clauseTokens);
    CHECK(dir.getSubCommand() == TokenKind::Material);
}

TEST_CASE("Parameters of load mesh clause") {
    Lexer lex;
    auto tokens = lex.scan("#pragma vp load mesh name(A) path(some/path)");
    Directive dir = Directive::create<DirectiveKind::Load>();
    tokens->erase(tokens->begin());
    const auto clauseTokens = *tokens;
    dir.populateClauses(clauseTokens);
    CHECK(dir.getSubCommand() == TokenKind::Mesh);
}

TEST_CASE("Clause population fails if required clauses are missing") {
    Lexer lex;
    const auto tokens = lex.scan("#pragma vp load mesh");
    Directive dir = Directive::create<DirectiveKind::Shader>();
    CHECK_THROWS(dir.populateClauses(*tokens));
}

TEST_CASE("Clause population fails if subcommand is of wrong kind") {
    Lexer lex;
    const auto tokens = lex.scan("#pragma vp load draw");
    Directive dir = Directive::create<DirectiveKind::Shader>();
    CHECK_THROWS(dir.populateClauses(*tokens));
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
    CHECK_FALSE(dir.hasSubCommand());
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

TEST_CASE("It is possible to call the Begin create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Begin>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Begin>());
}

TEST_CASE("It is possible to call the End create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::End>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::End>());
}

TEST_CASE("It is possible to call the Load create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Load>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Load>());
}

TEST_CASE("It is possible to call the Program create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Program>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Program>());
}

TEST_CASE("It is possible to call the Shader create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Shader>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Shader>());
}

TEST_CASE("It is possible to call the Texture create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Texture>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Texture>());
}

TEST_CASE("It is possible to call the CopyIn create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::CopyIn>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::CopyIn>());
}

TEST_CASE("It is possible to call the Option create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Option>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Option>());
}

TEST_CASE("It is possible to call the ResourceStore create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::ResourceStore>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::ResourceStore>());
}

TEST_CASE("It is possible to call the Include create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Include>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::Include>());
}

TEST_CASE("It is possible to call the FrameBuffer create method multiple times") {
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::FrameBuffer>());
    CHECK_NOTHROW(std::ignore = Directive::create<DirectiveKind::FrameBuffer>());
}

TEST_CASE("End Directive create method") {
    const Directive dir = Directive::create<DirectiveKind::End>();
    CHECK(dir.getDirectiveKind() == DirectiveKind::End);
    const auto clauses = dir.getClauseKinds();
    CHECK(clauses.empty());
}

TEST_CASE("Directive string representation of Unknown") {
    std::stringstream ss;
    ss << DirectiveKind::Unknown;
    CHECK(ss.str() == "Unknown");
}

TEST_CASE("Directive string representation of Shader") {
    std::stringstream ss;
    ss << DirectiveKind::Shader;
    CHECK(ss.str() == "Shader");
}

TEST_CASE("Directive string representation of Program") {
    std::stringstream ss;
    ss << DirectiveKind::Program;
    CHECK(ss.str() == "Program");
}

TEST_CASE("Directive string representation of Begin") {
    std::stringstream ss;
    ss << DirectiveKind::Begin;
    CHECK(ss.str() == "Begin");
}

TEST_CASE("Directive string representation of End") {
    std::stringstream ss;
    ss << DirectiveKind::End;
    CHECK(ss.str() == "End");
}

TEST_CASE("Directive string representation of Load") {
    std::stringstream ss;
    ss << DirectiveKind::Load;
    CHECK(ss.str() == "Load");
}

TEST_CASE("Directive string representation of Texture") {
    std::stringstream ss;
    ss << DirectiveKind::Texture;
    CHECK(ss.str() == "Texture");
}

TEST_CASE("Directive string representation of CopyIn") {
    std::stringstream ss;
    ss << DirectiveKind::CopyIn;
    CHECK(ss.str() == "CopyIn");
}

TEST_CASE("Directive string representation of Option") {
    std::stringstream ss;
    ss << DirectiveKind::Option;
    CHECK(ss.str() == "Option");
}

TEST_CASE("Directive string representation of ResourceStore") {
    std::stringstream ss;
    ss << DirectiveKind::ResourceStore;
    CHECK(ss.str() == "ResourceStore");
}

TEST_CASE("Directive string representation of Include") {
    std::stringstream ss;
    ss << DirectiveKind::Include;
    CHECK(ss.str() == "Include");
}

TEST_CASE("Directive string representation of FrameBuffer") {
    std::stringstream ss;
    ss << DirectiveKind::FrameBuffer;
    CHECK(ss.str() == "FrameBuffer");
}

TEST_CASE("It is possible to add a subcommand to a directive") {
    DirectiveBuilder builder;
    auto directive = builder.addSubCommand(TokenKind::Draw).build();
    CHECK(directive.hasSubCommand());
}

}
