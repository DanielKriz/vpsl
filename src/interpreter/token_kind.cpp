#include <vp/interpreter/token_kind.hpp>

namespace vp {

std::ostream &operator<<(std::ostream &os, const TokenKind &kind) {
    const std::string_view repr = [kind]() {
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
            case Draw: return "Draw";
            case IncludeDirective: return "IncludeDirective";
            case Path: return "Path";
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
    }();
    return os << repr;
}

} // namespace vp
