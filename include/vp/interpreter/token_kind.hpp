#ifndef VP_INTERPRETER_TOKEN_KIND_HPP
#define VP_INTERPRETER_TOKEN_KIND_HPP

#include <vp/types.hpp>
#include <vp/utils.hpp>

#include <iosfwd>

#include <fmt/ostream.h>

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
    Draw,
    
    IncludeDirective,
    Path,
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
    { "path", TokenKind::Path },
    { "draw", TokenKind::Draw },
    { "framebuffer", TokenKind::FrameBufferDirective },
    { "resource_store", TokenKind::ResourceStoreDirective },
    { "load", TokenKind::LoadDirective },
    { "mesh", TokenKind::Mesh },
    { "material", TokenKind::Material },
};

std::ostream &operator<<(std::ostream &os, const vp::TokenKind &kind);

} // namespace vp

template <>
struct fmt::formatter<vp::TokenKind> : ostream_formatter {};

#endif // VP_INTERPRETER_TOKEN_KIND_HPP
