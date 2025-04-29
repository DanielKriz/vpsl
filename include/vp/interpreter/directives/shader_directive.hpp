#ifndef VP_INTERPRETER_DIRECTIVE_SHADER_HPP
#define VP_INTERPRETER_DIRECTIVE_SHADER_HPP

#include <vp/interpreter/directives/directive_base.hpp>

namespace vp {

class ShaderDirective : public DirectiveBase {
public:
    ShaderDirective() : DirectiveBase {
        TokenKind::Name, TokenKind::Type, TokenKind::Prepend, TokenKind::Append } {};
private:
};

} // namespace vp

#endif // VP_INTERPRETER_DIRECTIVE_SHADER_HPP
