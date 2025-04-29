#ifndef VP_INTERPRETER_DIRECTIVE_PROGRAM_HPP
#define VP_INTERPRETER_DIRECTIVE_PROGRAM_HPP

#include <vp/interpreter/directives/directive_base.hpp>

namespace vp {

class ProgramDirective : public DirectiveBase {
public:
    ProgramDirective() : DirectiveBase {
        TokenKind::Name, TokenKind::Pre, TokenKind::Post, TokenKind::Shaders } {};
    void populate(const std::vector<Token> &tokens) override {}
};

} // namespace vp

#endif // VP_INTERPRETER_DIRECTIVE_PROGRAM_HPP
