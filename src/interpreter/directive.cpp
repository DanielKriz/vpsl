#include <vp/interpreter/directive.hpp>
#include <vp/description/shader_code.hpp>

namespace vp {

Directive::Directive(const Directive &other)
    : m_kind(other.m_kind), m_hasSubCommand(other.m_hasSubCommand)
    , m_subCommand(other.m_subCommand) {
    for (const auto clauseKind : other.getClauseKinds()) {
        m_clauses.insert(Directive::createEntry(clauseKind));
    }

    for (const auto subcommandKind : other.getSubCommandTokens()) {
        m_subCommandTokens.insert(subcommandKind);
    }
}

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

bool Directive::hasSubCommand() const noexcept {
    return m_hasSubCommand;
}

TokenKind Directive::getSubCommand() const noexcept {
    return m_subCommand;
}

const std::unordered_set<TokenKind> &Directive::getSubCommandTokens() const noexcept {
    return m_subCommandTokens;
}

void Directive::populateClauses(const std::vector<Token> &tokens) {
    std::vector<TokenIterator> clausePositions;

    auto it = tokens.cbegin();

    if (hasSubCommand()) {
        if (m_subCommandTokens.contains(it->getTokenKind())) {
            m_subCommand = it->getTokenKind();
        } else {
            throw std::runtime_error(
                fmt::format(
                    "Token '{}' is not a valid subcommand for directive '{}'",
                    it->getTokenKind(),
                    m_kind
                )
            );
        }
        ++it;
    }

    for (; it != tokens.cend(); ++it) {
        if (IClause::isClause(it->getTokenKind())) {
            clausePositions.push_back(it);
        }
    }

    for (auto &pos : clausePositions) {
        const auto kind = static_cast<ClauseKind>(pos->getTokenKind());
        if (m_populated.contains(kind)) {
            throw std::runtime_error(fmt::format("Clause {} is duplicit!", kind));
        }

        std::shared_ptr<IClause> pClause = nullptr;
        try {
            pClause = m_clauses.at(kind);
        } catch (std::out_of_range &e) {
            throw std::runtime_error(
                fmt::format(
                    "Unsupported clause {} for directive {}",
                    kind,
                    getDirectiveKind()
                )
            );
        }

        bool isValid = pClause->populate(pos, tokens.end());
        if (not isValid) {
            throw std::runtime_error(
                fmt::format(
                    "clause '{}' of directive '{}' is ill-formed",
                    pClause->getKind(),
                    getDirectiveKind()
                )
            );
        }
        m_populated.insert(kind);
    }
    for (const ClauseKind clause : m_required) {
        if (not m_populated.contains(clause)) {
            throw std::runtime_error(fmt::format("Required clause {} is not populated!", clause));
        }
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
    case Enable:
        return { Enable, std::make_shared<EnableClause>() };
    case Persistent:
        return { Persistent, std::make_shared<PersistentClause>() };
    case Value:
        return { Value, std::make_shared<ValueClause>() };
    case Format:
        return { Format, std::make_shared<FormatClause>() };
    default:
        throw std::runtime_error(fmt::format("Unsupported clause kind: {}", kind));
    }
}

template <>
Directive Directive::create<DirectiveKind::Shader>() {
    static DirectiveBuilder builder;
    if (not builder.isFinished()) {
        builder.setDirectiveKind(DirectiveKind::Shader)
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
               .addClause(ClauseKind::Name)
               .addClause(ClauseKind::Shaders)
               .addClause(ClauseKind::Draw)
               .addClause(ClauseKind::Mesh)
               .addClause(ClauseKind::Pre)
               .addClause(ClauseKind::Post);
        return builder.buildAndCopy();
    }
    return builder.copy();
}

template <>
Directive Directive::create<DirectiveKind::Load>() {
    static DirectiveBuilder builder;
    if (not builder.isFinished()) {
        builder.setDirectiveKind(DirectiveKind::Load)
               .addSubCommand(TokenKind::Texture)
               .addSubCommand(TokenKind::Material)
               .addSubCommand(TokenKind::Mesh)
               .addClause(ClauseKind::Name, true)
               .addClause(ClauseKind::Path, true);
        return builder.buildAndCopy();
    }
    return builder.copy();
}

template <>
Directive Directive::create<DirectiveKind::Texture>() {
    static DirectiveBuilder builder;
    if (not builder.isFinished()) {
        builder.setDirectiveKind(DirectiveKind::Texture)
               .addClause(ClauseKind::Name, true);
        return builder.buildAndCopy();
    }
    return builder.copy();
}

template <>
Directive Directive::create<DirectiveKind::Include>() {
    static DirectiveBuilder builder;
    if (not builder.isFinished()) {
        builder.setDirectiveKind(DirectiveKind::Include)
               .addClause(ClauseKind::Path, true);
        return builder.buildAndCopy();
    }
    return builder.copy();
}

template <>
Directive Directive::create<DirectiveKind::FrameBuffer>() {
    return { DirectiveKind::FrameBuffer };
}

template <>
Directive Directive::create<DirectiveKind::ResourceStore>() {
    static DirectiveBuilder builder;
    if (not builder.isFinished()) {
        builder.setDirectiveKind(DirectiveKind::ResourceStore)
               .addClause(ClauseKind::Path, true);
        return builder.buildAndCopy();
    }
    return builder.copy();
}

template <>
Directive Directive::create<DirectiveKind::CopyIn>() {
    return { DirectiveKind::CopyIn };
}

template <>
Directive Directive::create<DirectiveKind::Option>() {
    static DirectiveBuilder builder;
    if (not builder.isFinished()) {
        builder.setDirectiveKind(DirectiveKind::Option)
               .addClause(ClauseKind::Type, true)
               .addClause(ClauseKind::Enable)
               .addClause(ClauseKind::Value)
               .addClause(ClauseKind::Persistent);
        return builder.buildAndCopy();
    }
    return builder.copy();
}

template <>
Directive Directive::create<DirectiveKind::Begin>() {
    return { DirectiveKind::Begin };
}

template <>
Directive Directive::create<DirectiveKind::End>() {
    return { DirectiveKind::End };
}

DirectiveBuilder &DirectiveBuilder::setDirectiveKind(DirectiveKind kind) {
    m_directive.m_kind = kind;
    return *this;
}

DirectiveBuilder &DirectiveBuilder::addSubCommand(TokenKind kind) {
    m_directive.m_hasSubCommand = true;
    m_directive.m_subCommandTokens.insert(kind);
    return *this;
}

DirectiveBuilder &DirectiveBuilder::addClause(ClauseKind kind, bool isRequired) {
    using enum ClauseKind;
    auto &clauses = m_directive.m_clauses;
    clauses.emplace(Directive::createEntry(kind));

    if (isRequired) {
        m_directive.m_required.insert(kind);
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

std::ostream &operator<<(std::ostream &os, const DirectiveKind &kind) {
    const std::string_view repr = [kind]() {
        using enum DirectiveKind;
        switch(kind) {
            case Unknown: return "Unknown";
            case Shader: return "Shader";
            case Program: return "Program";
            case Begin: return "Begin";
            case End: return "End";
            case Load: return "Load";
            case Texture: return "Texture";
            case CopyIn: return "CopyIn";
            case Option: return "Option";
            case ResourceStore: return "ResourceStore";
            case Include: return "Include";
            case FrameBuffer: return "FrameBuffer";
            default:
                 throw std::runtime_error("Encountered Unknown Token!");
        }
    }();
    return os << repr;

}

} // namespace vp
