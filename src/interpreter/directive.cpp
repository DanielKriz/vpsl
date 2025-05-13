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
    return { DirectiveKind::Load };
}

template <>
Directive Directive::create<DirectiveKind::Texture>() {
    return { DirectiveKind::Texture };
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
    return { DirectiveKind::ResourceStore };
}

template <>
Directive Directive::create<DirectiveKind::CopyIn>() {
    return { DirectiveKind::CopyIn };
}

template <>
Directive Directive::create<DirectiveKind::Option>() {
    return { DirectiveKind::Option };
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
