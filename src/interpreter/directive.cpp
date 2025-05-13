#include <vp/interpreter/directive.hpp>
#include <vp/description/shader_code.hpp>

namespace vp {

DirectiveKind Directive::getDirectiveKind() const noexcept {
    return m_kind;
}

std::unordered_set<ClauseKind> Directive::getClauseKinds() const noexcept {
    std::unordered_set<ClauseKind> clauseKinds;
    for (const auto &kvp : m_clauses) {
        clauseKinds.insert(kvp.first);
    }
    return clauseKinds;
}

const std::unordered_set<ClauseKind> &Directive::getPopulatedClauses() const noexcept {
}

bool Directive::areClausesCorrect(const std::vector<Token> &tokens) const noexcept {
    return {};
}

void Directive::populateClauses(const std::vector<Token> &tokens) {
    std::vector<TokenIterator> clausePositions;

    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (IClause::isClause(it->getTokenKind())) {
            clausePositions.push_back(it);
        }
    }

    for (auto &pos : clausePositions) {
        const auto kind = static_cast<ClauseKind>(pos->getTokenKind());
        if (m_populated.contains(kind)) {
            // TODO
            throw std::runtime_error(fmt::format("Clause {} is duplicit!", "A"));
        }

        std::shared_ptr<IClause> pClause = nullptr;
        try {
            pClause = m_clauses.at(kind);
        } catch (std::runtime_error &e) {
            throw std::runtime_error(fmt::format("Unsupported clause {} for directive {}", "A", "D"));
        }

        bool isValid = pClause->populate(pos, tokens.end());
        if (not isValid) {
            throw std::runtime_error(fmt::format("clause {} of directive {} is ill-formed", "A", "D"));
        }
        m_populated.insert(kind);
    }
}

Directive Directive::clone() const {
    return { *this };
}

std::pair<ClauseKind, std::shared_ptr<IClause>> Directive::createEntry(ClauseKind kind) {
using enum ClauseKind;
    switch (kind) {
    case Name:
        return { Name, std::make_shared<NameClause>() };
    case Type:
        return { Type, std::make_shared<TypeClause>() };
    case Prepend:
        return { Prepend, std::make_shared<PrependClause>() };
    case Append:
        return { Append, std::make_shared<AppendClause>() };
    case Pre:
        return { Pre, std::make_shared<PreClause>() };
    case Post:
        return { Post, std::make_shared<PostClause>() };
    case Mesh:
        return { Mesh, std::make_shared<MeshClause>() };
    case Shaders:
        return { Shaders, std::make_shared<ShadersClause>() };
    case Draw:
        return { Draw, std::make_shared<DrawClause>() };
    case Path:
        return { Path, std::make_shared<PathClause>() };
    default:
        throw std::runtime_error(fmt::format("Unsupported clause kind: {}", kind));
    }
}

template <>
Directive Directive::create<DirectiveKind::Shader>() {
    static DirectiveBuilder builder;
    if (not builder.isFinished()) {
        builder.setDirectiveKind(DirectiveKind::Shader)
               .setDirectiveToken(TokenKind::ShaderDirective)
               .addClause(ClauseKind::Name)
               .addClause(ClauseKind::Type)
               .addClause(ClauseKind::Prepend)
               .addClause(ClauseKind::Append);
        return builder.buildAndCopy();
    } 
    return builder.copy();
}

template <>
Directive Directive::create<DirectiveKind::Program>() {
    static DirectiveBuilder builder;
    if (not builder.isFinished()) {
        builder.setDirectiveKind(DirectiveKind::Program)
               .setDirectiveToken(TokenKind::ProgramDirective)
               .addClause(ClauseKind::Name)
               // TODO
               // .addClause(ClauseKind::Shaders)
               .addClause(ClauseKind::Pre)
               .addClause(ClauseKind::Post);
        return builder.buildAndCopy();
    } 
    return builder.copy();
}

template <>
Directive Directive::create<DirectiveKind::Load>() {
    return { DirectiveKind::Load, TokenKind::LoadDirective };
}

template <>
Directive Directive::create<DirectiveKind::Texture>() {
    return { DirectiveKind::Texture, TokenKind::TextureDirective };
}

template <>
Directive Directive::create<DirectiveKind::Include>() {
    return { DirectiveKind::Include, TokenKind::IncludeDirective };
}

template <>
Directive Directive::create<DirectiveKind::FrameBuffer>() {
    return { DirectiveKind::FrameBuffer, TokenKind::FrameBufferDirective };
}

template <>
Directive Directive::create<DirectiveKind::ResourceStore>() {
    return { DirectiveKind::ResourceStore, TokenKind::ResourceStoreDirective };
}

template <>
Directive Directive::create<DirectiveKind::CopyIn>() {
    return { DirectiveKind::CopyIn, TokenKind::CopyInDirective };
}

template <>
Directive Directive::create<DirectiveKind::Option>() {
    return { DirectiveKind::Option, TokenKind::OptionDirective };
}

template <>
Directive Directive::create<DirectiveKind::Begin>() {
    return { DirectiveKind::Begin, TokenKind::BeginDirective };
}

template <>
Directive Directive::create<DirectiveKind::End>() {
    return { DirectiveKind::End, TokenKind::EndDirective };
}

DirectiveBuilder &DirectiveBuilder::setDirectiveKind(DirectiveKind kind) {
    m_directive.m_kind = kind;
    return *this;
}

DirectiveBuilder &DirectiveBuilder::setDirectiveToken(TokenKind kind) {
    m_directive.m_tokenKind = kind;
    return *this;
}

DirectiveBuilder &DirectiveBuilder::addClause(ClauseKind kind) {
    using enum ClauseKind;
    auto &clauses = m_directive.m_clauses;
    clauses.emplace(Directive::createEntry(kind));
    }
    return *this;
}

Directive &&DirectiveBuilder::build() {
    return std::move(m_directive);
}

Directive DirectiveBuilder::buildAndCopy() {
    m_isFinished = true;
    return m_directive.clone();
}

Directive DirectiveBuilder::copy() {
    if (not isFinished()) {
        throw std::runtime_error("Cannot copy unfinished directive!");
    }
    return m_directive.clone();
}



} // namespace vp
