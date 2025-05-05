#include <vp/interpreter/parser.hpp>

namespace vp {

std::optional<Directive> Parser::createDirectiveFromToken(const Token &token) {
    TokenKind kind = token.getTokenKind();
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
    default:
        return {};
    }
}

void Parser::setCurrentNode(vp::build::INode &pOther) {
}

vp::build::INode &Parser::getCurrentNode() {
    return m_CurrentNode;
}

bool Parser::isCurrentNodeRoot() const {
    return {};
}

void Parser::pushScope(ParserStage stage) {
}

void Parser::popScope() {
}

ParserStage Parser::peekScope() const {
    return {};
}

bool Parser::isScopeEmpty() const noexcept {
    return {};
}

}
