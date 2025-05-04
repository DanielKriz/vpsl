#ifndef VP_INTERPRETER_CLAUSE_HPP
#define VP_INTERPRETER_CLAUSE_HPP

#include <vector>
#include <iterator>

#include <vp/types.hpp>
#include <vp/interpreter/token.hpp>

namespace vp {

enum class ClauseKind {
    Name = static_cast<enum32>(TokenKind::Name),
    Type = static_cast<enum32>(TokenKind::Type),
    Pre = static_cast<enum32>(TokenKind::Pre),
    Post = static_cast<enum32>(TokenKind::Post),
    Prepend = static_cast<enum32>(TokenKind::Prepend),
    Append = static_cast<enum32>(TokenKind::Append),
};

using TokenIterator = std::vector<Token>::const_iterator;

struct IClause {
    virtual ~IClause() = default;
    static constexpr u64 PARAMETER_LIMIT = 256;
    [[nodiscard]] virtual ClauseKind getKind() const noexcept = 0;
    [[nodiscard]] virtual u64 getMinParameters() const noexcept = 0;
    [[nodiscard]] virtual u64 getMaxParameters() const noexcept = 0;
    [[nodiscard]] virtual bool isValidClause(const std::vector<Token> &tokens) const = 0;
    [[nodiscard]] virtual bool isValidClause(TokenIterator it, const TokenIterator &end) const = 0;
    [[nodiscard]] virtual const std::vector<std::string> &getParameters() const noexcept = 0;
    [[nodiscard]] virtual bool isPopulated() const noexcept = 0;
    virtual void populate(const std::vector<Token> &tokens) = 0;
    virtual void populate(TokenIterator it, const TokenIterator &end) = 0;
    static bool isClause(TokenKind kind) noexcept;
    static bool isClause(const Token &token) noexcept;
};

class ClauseBase : public IClause {
public:
    ~ClauseBase() override = default;
    [[nodiscard]] bool isValidClause(const std::vector<Token> &tokens) const override;
    [[nodiscard]] bool isValidClause(TokenIterator it, const TokenIterator &end) const override;
    [[nodiscard]] bool isPopulated() const noexcept override { return m_populated; }
    [[nodiscard]] const std::vector<std::string> &getParameters() const noexcept override {
        return m_parameters;
    }
    void populate(const std::vector<Token> &tokens) override;
    void populate(TokenIterator it, const TokenIterator &end) override;
protected:
    std::vector<std::string> m_parameters;
    bool m_populated { false };
};

template <ClauseKind Kind, u64 Min = 1, u64 Max = 1>
struct Clause final : public ClauseBase {
    ~Clause() override = default;
    [[nodiscard]] inline ClauseKind getKind() const noexcept override { return Kind; }
    [[nodiscard]] inline u64 getMinParameters() const noexcept override { return Min; }
    [[nodiscard]] inline u64 getMaxParameters() const noexcept override { return Max; }
};

template <ClauseKind Kind>
using ParameterClause = Clause<Kind, 1, IClause::PARAMETER_LIMIT>;

using NameClause = Clause<ClauseKind::Name>;
using TypeClause = Clause<ClauseKind::Type>;
using PreClause = ParameterClause<ClauseKind::Pre>;
using PostClause = ParameterClause<ClauseKind::Post>;
using AppendClause = ParameterClause<ClauseKind::Append>;
using PrependClause = ParameterClause<ClauseKind::Prepend>;

} // namespace vp

#endif // VP_INTERPRETER_CLAUSE_HPP
