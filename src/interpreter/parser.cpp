#include <vp/interpreter/parser.hpp>

namespace vp {

std::optional<Directive> Parser::createDirectiveFromToken(const Token &token) {
    const TokenKind kind = token.getTokenKind();
    switch (kind) {
    case TokenKind::ShaderDirective:
        return Directive::create<DirectiveKind::Shader>();
    case TokenKind::ProgramDirective:
        return Directive::create<DirectiveKind::Program>();
    case TokenKind::LoadDirective:
        return Directive::create<DirectiveKind::Load>();
    case TokenKind::BeginDirective:
        return Directive::create<DirectiveKind::Begin>();
    case TokenKind::EndDirective:
        return Directive::create<DirectiveKind::End>();
    case TokenKind::TextureDirective:
        return Directive::create<DirectiveKind::Texture>();
    case TokenKind::FrameBufferDirective:
        return Directive::create<DirectiveKind::FrameBuffer>();
    case TokenKind::OptionDirective:
        return Directive::create<DirectiveKind::Option>();
    case TokenKind::CopyInDirective:
        return Directive::create<DirectiveKind::CopyIn>();
    case TokenKind::IncludeDirective:
        return Directive::create<DirectiveKind::Include>();
    case TokenKind::ResourceStoreDirective:
        return Directive::create<DirectiveKind::ResourceStore>();
    default:
        return {};
    }
}

void Parser::pushGlobalShaderScope() {
    if (m_stage != ParserScope::Global) {
        throw std::runtime_error("Cannot push to global shader from different than global scope");
    }
    m_stage = ParserScope::GlobalShader;
}

void Parser::pushScope() {
    using enum ParserScope;
    switch (m_stage) {
    case Global:
        m_stage = Program;
        break;
    case Program:
        m_stage = Shader;
        break;
    case GlobalShader:
    case Shader:
        throw std::runtime_error("Invalid scope!");
    }
}

void Parser::pushScope(ParserScope stage) {
}

void Parser::popScope() {
    using enum ParserScope;
    switch (m_stage) {
    case GlobalShader:
        m_stage = Global;
        break;
    case Shader:
        m_stage = Program;
        break;
    case Program:
        m_stage = Global;
        break;
    case Global:
        throw std::runtime_error("Invalid scope!");
    }
}

ParserScope Parser::peekScope() const {
    return m_stage;
}

bool Parser::isScopeEmpty() const noexcept {
    return {};
}

void Parser::addProgramDescription(desc::ProgramDescription &desc) {
}

void Parser::addProgramDescription(desc::ProgramDescription &&desc) {
    m_programDescriptions.emplace_back(std::move(desc));
}

} // namespace vp
