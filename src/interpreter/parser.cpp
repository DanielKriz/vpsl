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
    case TokenKind::Texture:
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

void Parser::addProgramDescription(desc::ProgramDescription &desc) {
    m_programDescriptions.push_back(desc);
}

void Parser::addProgramDescription(desc::ProgramDescription &&desc) {
    m_programDescriptions.emplace_back(std::move(desc));
}

std::vector<desc::ProgramDescription> Parser::createExecutionSequenceDescription() {
    return m_programDescriptions;
}

ShaderCode *Parser::shaderCodeFromDirective(Directive &dir, desc::ProgramDescriptionBuilder &builder) {
    auto name = dir.getParameter<ClauseKind::Name>();
    ShaderCode *pShaderCode { nullptr };
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

    auto typeParam = dir.getParameter<ClauseKind::Type>();
    if (typeParam.has_value()) {
        auto type = *utils::mapStringToEnumKind<ShaderCodeKind>(*typeParam);
        pShaderCode->setKind(type);
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
            auto *code = m_store.emplace(shader);
            pShaderCode->addToPrependSet(*code);
        }
        m_store.addDependencies(pShaderCode->getName(), *prependSet);
    }

    auto appendSet = dir.getParameters<ClauseKind::Append>();
    if (appendSet.has_value()) {
        for (const auto &shader : *appendSet) {
            auto *code = m_store.emplace(shader);
            pShaderCode->addToAppendSet(*code);
        }
        m_store.addDependencies(pShaderCode->getName(), *appendSet);
    }

    return pShaderCode;
}

void Parser::applyOptionDirective(Directive &dir, Options &localOpts) {
    auto type = *dir.getParameter<ClauseKind::Type>();
    auto enabledParam = dir.getParameter<ClauseKind::Enable>();
    auto valueParam = dir.getParameter<ClauseKind::Value>();

    if (enabledParam.has_value() and valueParam.has_value()) {
        throw std::runtime_error(
            "Only one of value or enable clauses can be defined at the same time"
        );
    }

    if (enabledParam.has_value()) {
        handleEnableOption(dir, localOpts);
    } else if (valueParam.has_value()) {
        handleValueOption(dir, localOpts);
    } else {
        throw std::runtime_error("Either value or enabled has to be defined for option!");
    }
}

bool Parser::isOptionPersistent(Directive &dir) {
    auto persistenParam = dir.getParameter<ClauseKind::Persistent>();
    bool isPersistent = false;
    if (persistenParam.has_value()) {
        isPersistent = utils::stringToBool(
            *dir.getParameter<ClauseKind::Persistent>()
        );
    }
    return isPersistent;
}

void Parser::handleValueOption(Directive &dir, Options &localOpts) {
    auto type = *dir.getParameter<ClauseKind::Type>();
    auto enabledParam = dir.getParameter<ClauseKind::Enable>();
    auto valueParam = dir.getParameter<ClauseKind::Value>();

    const bool isPersistent = isOptionPersistent(dir);

    if (type == "front_polygon_mode") {
        const auto value = utils::mapStringToEnumKind<gl::PolygonMode>(*valueParam);
        if (not value.has_value()) {
            throw std::runtime_error(
                fmt::format("Not supported option '{}' for front polygon mode",
                *valueParam)
            );
        }
        localOpts.frontFacePolygonMode = *value;
        if (isPersistent) {
            getGlobalOptions().frontFacePolygonMode = *value;
        }
    } else if (type == "back_polygon_mode") {
        const auto value = utils::mapStringToEnumKind<gl::PolygonMode>(*valueParam);
        if (not value.has_value()) {
            throw std::runtime_error(
                fmt::format("Not supported option '{}' for back polygon mode",
                *valueParam)
            );
        }
        localOpts.backFacePolygonMode = *value;
        if (isPersistent) {
            getGlobalOptions().backFacePolygonMode = *value;
        }
    } else if (type == "polygon_mode") {
        const auto value = utils::mapStringToEnumKind<gl::PolygonMode>(*valueParam);
        if (not value.has_value()) {
            throw std::runtime_error(
                fmt::format("Not supported option '{}' for back polygon mode",
                *valueParam)
            );
        }
        localOpts.backFacePolygonMode = *value;
        localOpts.frontFacePolygonMode = *value;
        if (isPersistent) {
            getGlobalOptions().backFacePolygonMode = *value;
        }
    } else if (type == "culling_mode") {
        const auto value = utils::mapStringToEnumKind<gl::CullingMode>(*valueParam);
        if (not value.has_value()) {
            throw std::runtime_error(
                fmt::format("Not supported option '{}' for culling mode",
                *valueParam)
            );
        }
        localOpts.cullingMode = *value;
        if (isPersistent) {
            getGlobalOptions().cullingMode = *value;
        }
    } else if (type == "front_face_mode") {
        const auto value = utils::mapStringToEnumKind<gl::FrontFaceMode>(*valueParam);
        if (not value.has_value()) {
            throw std::runtime_error(
                fmt::format("Not supported option '{}' for front face mode",
                *valueParam)
            );
        }
        localOpts.frontFaceMode = *value;
        if (isPersistent) {
            getGlobalOptions().frontFaceMode = *value;
        }
    } else if (type == "src_blending_factor") {
        const auto value = utils::mapStringToEnumKind<gl::BlendingFactor>(*valueParam);
        if (not value.has_value()) {
            throw std::runtime_error(
                fmt::format("Not supported option '{}' for source blending mode",
                *valueParam)
            );
        }
        localOpts.srcBlendFactor = *value;
        if (isPersistent) {
            getGlobalOptions().srcBlendFactor = *value;
        }
    } else if (type == "dst_blending_factor") {
        const auto value = utils::mapStringToEnumKind<gl::BlendingFactor>(*valueParam);
        if (not value.has_value()) {
            throw std::runtime_error(
                fmt::format("Not supported option '{}' for destination blending mode",
                *valueParam)
            );
        }
        localOpts.dstBlendFactor = *value;
        if (isPersistent) {
            getGlobalOptions().dstBlendFactor = *value;
        }
    } else if (type == "depth_function") {
        const auto value = utils::mapStringToEnumKind<gl::DepthFunction>(*valueParam);
        if (not value.has_value()) {
            throw std::runtime_error(
                fmt::format("Not supported option '{}' for depth function",
                *valueParam)
            );
        }
        localOpts.depthFunction = *value;
        if (isPersistent) {
            getGlobalOptions().depthFunction = *value;
        }
    } else {
        throw std::runtime_error("For this option the value clause is not defined");
    }

}

void Parser::handleEnableOption(Directive &dir, Options &localOpts) {
    auto type = *dir.getParameter<ClauseKind::Type>();
    auto enabledParam = dir.getParameter<ClauseKind::Enable>();
    auto valueParam = dir.getParameter<ClauseKind::Value>();

    const bool isPersistent = isOptionPersistent(dir);

    const auto isEnabled = utils::stringToBool(
        *dir.getParameter<ClauseKind::Enable>()
    );

    if (type == "depth_test") {
        localOpts.isDepthTestEnabled = isEnabled;
        if (isPersistent) {
            getGlobalOptions().isDepthTestEnabled = isEnabled;
        }
    } else if ( type != "blending") {
        localOpts.isBlendingEnabled = isEnabled;
        if (isPersistent) {
            getGlobalOptions().isBlendingEnabled = isEnabled;
        }
    } else if (type != "face_culling") {
        localOpts.isFaceCullingEnabled = isEnabled;
        if (isPersistent) {
            getGlobalOptions().isFaceCullingEnabled = isEnabled;
        }
    } else {
        throw std::runtime_error("For this option the enabled clause is not defined");
    }
}

} // namespace vp
