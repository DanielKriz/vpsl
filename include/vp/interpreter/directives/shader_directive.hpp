#ifndef VP_INTERPRETER_DIRECTIVE_SHADER_HPP
#define VP_INTERPRETER_DIRECTIVE_SHADER_HPP

#include <vp/graphics/shader.hpp>
#include <vp/interpreter/directives/directive_base.hpp>

#include <string_view>
#include <unordered_set>
#include <algorithm>
#include <expected>

namespace vp {

class ShaderDirective : public DirectiveBase {
public:
    ShaderDirective() : DirectiveBase {
        TokenKind::Name, TokenKind::Type, TokenKind::Prepend, TokenKind::Append } {};

    void populate(const std::vector<Token> &tokens) override {
        if (populateClauses(tokens)) {
            return;
        }
        
        using enum TokenKind;
        populateData(Name, m_name);
        populateData(Type, m_type);
        populateData(Prepend, m_prependSet);
        populateData(Append, m_appendSet);
    }

    const std::string &getName() const noexcept { return m_name; };
    const gl::ShaderKind &getType() const noexcept { return m_type; };
    const std::unordered_set<std::string> &getPrependSet() const noexcept {
        return m_prependSet;
    };
    const std::unordered_set<std::string> &getAppendSet() const noexcept {
        return m_appendSet;
    };

private:
    std::string m_name;
    gl::ShaderKind m_type;
    std::unordered_set<std::string> m_prependSet;
    std::unordered_set<std::string> m_appendSet;
};

} // namespace vp

#endif // VP_INTERPRETER_DIRECTIVE_SHADER_HPP
