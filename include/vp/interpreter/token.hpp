#ifndef VP_INTERPRETER_TOKEN_HPP
#define VP_INTERPRETER_TOKEN_HPP

#include <string>

#include <fmt/core.h>

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp {

enum class TokenKind {
    LeftBracket,
    RightBracket,
    LeftParen,
    RightParen,
    Comma,
    Pragma,
    Namespace,

    Identifier,

    ShaderDirective,
    Type,
    Name,
    Append,
    Prepend,
    
    ProgramDirective,
    Pre,
    Post,
    Shaders,

    IncludeDirective,
    OptionDirective,

    TextureDirective,
    Format,

    LoadDirective,
    Mesh,
    Material,
    Texture,

    FrameBufferDirective,

    CopyInDirective,
    BeginDirective,
    EndDirective,

    SourceLine,
};

template <>
inline utils::StringMap<TokenKind> utils::StringToEnumMap<TokenKind>::map = {
    { "#pragma" , TokenKind::Pragma },
    { "name" , TokenKind::Name },
    { "append" , TokenKind::Append },
    { "prepend" , TokenKind::Prepend },
    { "pre" , TokenKind::Pre },
    { "post" , TokenKind::Post },
    { "texture" , TokenKind::Texture },
    { "vp" , TokenKind::Namespace },
    { "shader", TokenKind::ShaderDirective },
    { "shaders", TokenKind::Shaders },
    { "type", TokenKind::Type },
    { "program", TokenKind::ProgramDirective },
    { "copyin", TokenKind::CopyInDirective },
    { "include", TokenKind::IncludeDirective },
    { "end", TokenKind::EndDirective },
    { "begin", TokenKind::BeginDirective },
    { "option", TokenKind::OptionDirective },
    { "format", TokenKind::Format },
    { "framebuffer", TokenKind::FrameBufferDirective },
    { "load", TokenKind::LoadDirective },
    { "model", TokenKind::Mesh },
    { "material", TokenKind::Material },
};


class Token final {
public:
    Token() = default;
    Token(std::string lexeme, TokenKind kind, u64 line) :
        m_lexeme(std::move(lexeme)), m_tokenKind(kind), m_line(line) {};

    [[nodiscard]] TokenKind getTokenKind() const noexcept { return m_tokenKind; }
    [[nodiscard]] u64 getLineNumber() const noexcept { return m_line; }
    [[nodiscard]] const std::string &getLexeme() const noexcept { return m_lexeme; }

    friend std::ostream &operator<<(std::ostream &os, const Token &token) {
        const auto repr = fmt::format("({}) {}: '{}'", token.m_line, static_cast<enum32>(token.m_tokenKind), token.m_lexeme);
        return os << repr;
    }
private:
    std::string m_lexeme;
    TokenKind m_tokenKind;
    u64 m_line;
};

} // namespace vp

#endif // VP_INTERPRETER_TOKEN_HPP
