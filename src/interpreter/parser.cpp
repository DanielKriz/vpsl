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

std::vector<desc::ProgramDescription> Parser::createExecutionSequenceDescription() {
    return m_programDescriptions;
}

ShaderCode *Parser::shaderCodeFromDirective(Directive &dir, desc::ProgramDescriptionBuilder &builder) {
    auto name = dir.getParameter<ClauseKind::Name>();
    ShaderCode *pShaderCode {};
    if (name.has_value() and not name->empty()) {
        if (peekScope() == ParserScope::Global) {
            name = "global:" + *name;
        } else {
            name = builder.createShaderName(*name);
        }
        pShaderCode = m_store.emplace(*name);
    } else {
        pShaderCode = m_store.emplaceUnnamed();
    }

    auto type = dir.getParameter<ShaderCodeKind>();
    if (type.has_value()) {
        pShaderCode->setKind(*type);
    } else {
        pShaderCode->setKind(ShaderCodeKind::Generic);
    }

    // add the shader to the program
    if (peekScope() != ParserScope::Global) {
        builder.addShaderCode(*pShaderCode);
    }

    auto prependSet = dir.getParameters<ClauseKind::Prepend>();
    if (prependSet.has_value()) {
        for (const auto &shader : *prependSet) {
            fmt::println("Prepending {}", shader);
            auto *code = m_store.emplace(shader);
            pShaderCode->addToPrependSet(*code);
        }
        m_store.addDependencies(pShaderCode->getName(), *prependSet);
    }

    auto appendSet = dir.getParameters<ClauseKind::Append>();
    if (appendSet.has_value()) {
        for (const auto &shader : *appendSet) {
            fmt::println("Append {}", shader);
            auto *code = m_store.emplace(shader);
            pShaderCode->addToAppendSet(*code);
        }
        m_store.addDependencies(pShaderCode->getName(), *appendSet);
    }

    return pShaderCode;
}

} // namespace vp
