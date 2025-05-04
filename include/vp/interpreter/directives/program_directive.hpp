#ifndef VP_INTERPRETER_DIRECTIVE_PROGRAM_HPP
#define VP_INTERPRETER_DIRECTIVE_PROGRAM_HPP

#include <vp/interpreter/directives/directive_base.hpp>

namespace vp {

class ProgramDirective : public DirectiveBase {
public:
    void populate(const std::vector<Token> &tokens) override {
        if (populateClauses(tokens)) {
            return;
        }
    }
    ProgramDirective() : DirectiveBase (DirectiveKind::Program, {
        TokenKind::Name, TokenKind::Pre, TokenKind::Post, TokenKind::Shaders }) {};

    // TODO: make this efficient
    std::optional<std::vector<std::string>> getParameters(TokenKind kind) {
        auto *pClause =  getClause(kind);
        if (pClause == nullptr) {
            return {};
        }
        return pClause->getParameters();
    }
};

} // namespace vp

#endif // VP_INTERPRETER_DIRECTIVE_PROGRAM_HPP
