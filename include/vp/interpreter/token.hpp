#ifndef VP_INTERPRETER_TOKEN_HPP
#define VP_INTERPRETER_TOKEN_HPP

#include <string>

#include <fmt/core.h>

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp {

enum class TokenKind : u8 {
    Unknown,

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
    ResourceStoreDirective,

    SourceLine,
};

template <>
inline utils::StringViewMap<TokenKind> utils::StringToEnumMap<TokenKind>::map = {
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
    { "mesh", TokenKind::Mesh },
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
        const auto repr = fmt::format("Token({}, {}, '{}')", token.m_line, enumToString(token.m_tokenKind), token.m_lexeme);
        return os << repr;
    }

private:
    static std::string_view enumToString(TokenKind kind) {
        using enum TokenKind;
        switch(kind) {
        case Unknown: return "Unknown";
        case LeftBracket: return "LeftBracket";
        case RightBracket: return "RightBracket";
        case LeftParen: return "LeftParen";
        case RightParen: return "RightParen";
        case Comma: return "Comman";
        case Pragma: return "Pragma";
        case Namespace: return "Namespace";
        case Identifier: return "Identifier";
        case ShaderDirective: return "ShaderDirective";
        case Type: return "Type";
        case Name: return "Name";
        case Append: return "Append";
        case Prepend: return "Prepend";
        case ProgramDirective: return "ProgramDirective";
        case Pre: return "Pre";
        case Post: return "Post";
        case Shaders: return "Shaders";
        case IncludeDirective: return "IncludeDirective";
        case OptionDirective: return "OptionDirective";
        case TextureDirective: return "TextureDirective";
        case Format: return "Format";
        case LoadDirective: return "LoadDirective";
        case Mesh: return "Mesh";
        case Material: return "Material";
        case Texture: return "Texture";
        case FrameBufferDirective: return "FrameBufferDirective";
        case CopyInDirective: return "CopyInDirective";
        case BeginDirective: return "BeginDirective";
        case EndDirective: return "EndDirective";
        case SourceLine: return "SourceLine";
        default:
             throw std::runtime_error("Encountered Unknown Token!");
        }
    }

    std::string m_lexeme;
    TokenKind m_tokenKind { TokenKind::Unknown };
    u64 m_line { 0 };
};

} // namespace vp

#endif // VP_INTERPRETER_TOKEN_HPP
