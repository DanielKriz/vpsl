#ifndef VP_INTERPRETER_DIRECTIVE_HPP
#define VP_INTERPRETER_DIRECTIVE_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <vp/interpreter/clause.hpp>
#include <vp/interpreter/directives/directive_interface.hpp>

namespace vp {

#if 0
class Directive : public IDirective {
#else
class Directive {
#endif
public:
    /// @brief this class is constructible only by the provided builder.
    friend class DirectiveBuilder;

    /// @brief method for creation of directives with builder.
    /// By default it only throws an error, because it should be implemented with template
    /// specialization.
    template <DirectiveKind K>
    [[nodiscard]] static Directive create() { throw std::runtime_error("not implemented!"); }

    /// @brief Getter for directive's kind
    [[nodiscard]] DirectiveKind getDirectiveKind() const noexcept;
    /// @brief Getter for kinds of clauses that compose the directive.
    [[nodiscard]] std::unordered_set<ClauseKind> getClauseKinds() const noexcept;
    /// @brief Getter for reference to populated clauses.
    [[nodiscard]] const std::unordered_set<ClauseKind> &getPopulatedClauses() const noexcept;
    /// @brief Checks whether a stream of tokens is a valid set of clauses for this directive.
    bool areClausesCorrect(const std::vector<Token> &tokens) const noexcept;
    /// @brief Populates held clauses with data from token stream.
    void populateClauses(const std::vector<Token> &tokens);
    /// @brief Clone method that provides unified interface over the copy ctor.
    Directive clone() const;

    Directive(const Directive &other) = default;
    Directive(Directive &&other) noexcept = default;
    Directive &operator=(const Directive &other) = default;
    Directive &operator=(Directive &&other) noexcept = default;

    ~Directive() = default;

    /// @brief Getter for a data held by some particular clause
    ///
    /// If that particular clause is not held by this directive, then no value is wrapped into the
    /// optional return value.
    ///
    /// @tparam K particular clauses kind that is used for searching.
    /// @tparam T return type of the method.
    template <ClauseKind K, typename T = std::string>
    std::optional<T> getParameter() const noexcept;

    /// @brief Getter for a data held by some particular clause with multiple parameters
    ///
    /// If that particular clause is not present in this directive then no value is going to be
    /// wrapped into the optional return value.
    ///
    /// @tparam K particular clauses kind that is used for searching.
    template <ClauseKind K>
    std::optional<std::vector<std::string>> getParameters() const noexcept;

    /// @brief Getter for data that returns an enum from the type clause
    ///
    /// @tparam E enum kind which the method should return.
    /// @tparam K particular clause kind that should contain value mappable to E
    template <EnumKind E, ClauseKind K = ClauseKind::Type>
    std::optional<E> getParameter() const noexcept;

private:
    /// This class is constructible only by the provided builder type.
    Directive() = default;

    /// @brief Constructor for simple directives without any clauses
    /// This is a simple optimization, so that we do not have to initialize a whole new builder
    /// for a directive that does not have, not should have, any clauses.
    Directive(DirectiveKind kind, TokenKind tokenKind) : m_kind(kind), m_tokenKind(tokenKind) {}

    /// @brief Getter for a pointer to some particular clause.
    ///
    /// If the directive does not hold that particular clause kind, then no pointer is wrapped into
    /// the optional return value.
    template <ClauseKind K>
    [[nodiscard]] std::optional<const IClause *> getClause() const noexcept {
        if (auto it = m_clauses.find(K); it != m_clauses.end()) {
            return it->second.get();
        }
        return {};
    };

    /// @brief Kind of the directive. It is used as a direct identifier.
    DirectiveKind m_kind { DirectiveKind::Unknown };
    /// @brief Kind of the token that denotes this directive.
    TokenKind m_tokenKind { TokenKind::Unknown };
    /// @brief Map of clauses that are held by this directive instance.
    std::unordered_map<ClauseKind, std::shared_ptr<IClause>> m_clauses;
    /// @brief Set of clauses that are already populated.
    /// It is used for checking whether some clause is already closed, multiple definition of
    /// one particular clause results in an error.
    std::unordered_set<ClauseKind> m_populated;
};

template <ClauseKind K, typename T>
std::optional<T> Directive::getParameter() const noexcept {
    auto pClause = getClause<K>();
    if (pClause.has_value()) {
        return std::string { pClause.value()->getParameters()[0] };
    }
    return {};
}

template <ClauseKind K>
std::optional<std::vector<std::string>> Directive::getParameters() const noexcept {
    auto pClause = getClause<K>();
    if (pClause.has_value()) {
        return pClause.value()->getParameters();
    }
    return {};
}

template <EnumKind E, ClauseKind K>
std::optional<E> Directive::getParameter() const noexcept {
    const auto value = getParameter<K>();
    return value.has_value() ? utils::mapStringToEnumKind<E>(*value) : std::optional<E>();
}


/// @brief Builder for the Directive class.
///
/// This is the only approach to create a new instance of Directive class.
class DirectiveBuilder {
public:
    /// @brief Sets the directive kind of directive.
    DirectiveBuilder &setDirectiveKind(DirectiveKind kind);
    /// @brief Sets the token kind of directive that shall be searched during scanning.
    DirectiveBuilder &setDirectiveToken(TokenKind kind);
    /// @brief Adds clause to the directive.
    DirectiveBuilder &addClause(ClauseKind kind);
    /// @brief Copies already built (by this particular builder) directive.
    /// @throws runtime_error if the directive is not build.
    Directive copy();
    /// @brief Builds directive. The directive is moved and the builder no longer owns it.
    Directive &&build();
    /// @brief Builds the directive and copies it. The builder still owns this directive.
    Directive buildAndCopy();
    /// @brief Checks whether the builder finished building.
    [[nodiscard]] bool isFinished() const noexcept { return m_isFinished; }
private:
    /// @brief Directive that is composed by this builder.
    Directive m_directive;
    /// @brief Flag that shows whether the builder already finished building.
    bool m_isFinished { false };
};

} // namespace vp

#endif // VP_INTERPRETER_DIRECTIVE_HPP
