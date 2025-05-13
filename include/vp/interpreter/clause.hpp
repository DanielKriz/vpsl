#ifndef VP_INTERPRETER_CLAUSE_HPP
#define VP_INTERPRETER_CLAUSE_HPP

#include <iosfwd>
#include <vector>

#include <vp/interpreter/token.hpp>
#include <vp/types.hpp>

#include <fmt/ostream.h>

namespace vp {

enum class ClauseKind : u8 {
    Name = static_cast<enum32>(TokenKind::Name),
    Type = static_cast<enum32>(TokenKind::Type),
    Pre = static_cast<enum32>(TokenKind::Pre),
    Post = static_cast<enum32>(TokenKind::Post),
    Draw = static_cast<enum32>(TokenKind::Draw),
    Path = static_cast<enum32>(TokenKind::Path),
    Shaders = static_cast<enum32>(TokenKind::Shaders),
    Mesh = static_cast<enum32>(TokenKind::Mesh),
    Prepend = static_cast<enum32>(TokenKind::Prepend),
    Append = static_cast<enum32>(TokenKind::Append),
};

using TokenIterator = std::vector<Token>::const_iterator;

struct IClause {
    IClause() = default;
    IClause(const IClause &) = default;
    IClause(IClause &&) noexcept = default;
    IClause &operator=(const IClause &) = default;
    IClause &operator=(IClause &&) noexcept = default;
    virtual ~IClause() = default;

    static constexpr u64 PARAMETER_LIMIT = 256;
    [[nodiscard]] virtual ClauseKind getKind() const noexcept = 0;
    [[nodiscard]] virtual u64 getMinParameters() const noexcept = 0;
    [[nodiscard]] virtual u64 getMaxParameters() const noexcept = 0;
    [[nodiscard]] virtual bool
    isValidClause(const std::vector<Token> &tokens) const = 0;
    [[nodiscard]] virtual bool isValidClause(TokenIterator it,
                                             const TokenIterator &end) const = 0;
    [[nodiscard]] virtual const std::vector<std::string> &
    getParameters() const noexcept = 0;
    [[nodiscard]] virtual bool isPopulated() const noexcept = 0;
    virtual bool populate(const std::vector<Token> &tokens) = 0;
    virtual bool populate(TokenIterator it, const TokenIterator &end) = 0;
    static bool isClause(TokenKind kind) noexcept;
    static bool isClause(const Token &token) noexcept;
};

class ClauseBase : public IClause {
public:
    ClauseBase() = default;
    ClauseBase(const ClauseBase &) = default;
    ClauseBase(ClauseBase &&) noexcept = default;
    ClauseBase &operator=(const ClauseBase &) = default;
    ClauseBase &operator=(ClauseBase &&) noexcept = default;
    ~ClauseBase() override = default;

    [[nodiscard]] bool isValidClause(const std::vector<Token> &tokens) const override;
    [[nodiscard]] bool isValidClause(TokenIterator it, const TokenIterator &end) const override;
    [[nodiscard]] bool isPopulated() const noexcept override { return m_populated; }
    [[nodiscard]] const std::vector<std::string> &getParameters() const noexcept override {
        return m_parameters;
    }
    bool populate(const std::vector<Token> &tokens) override;
    bool populate(TokenIterator it, const TokenIterator &end) override;
protected:
    std::vector<std::string> m_parameters;
    bool m_populated { false };
};

template <ClauseKind Kind, u64 Min = 1, u64 Max = 1>
requires (Max >= Min and Min > 0 and Max > 0)
struct Clause final : public ClauseBase {
    Clause() = default;
    Clause(const Clause &) = default;
    Clause(Clause &&) noexcept = default;
    Clause &operator=(const Clause &) = default;
    Clause &operator=(Clause &&) noexcept = default;
    ~Clause() override = default;

    [[nodiscard]] ClauseKind getKind() const noexcept override { return Kind; }
    [[nodiscard]] u64 getMinParameters() const noexcept override { return Min; }
    [[nodiscard]] u64 getMaxParameters() const noexcept override { return Max; }
};

template <ClauseKind Kind>
using ParameterClause = Clause<Kind, 1, IClause::PARAMETER_LIMIT>;

using NameClause = Clause<ClauseKind::Name>;
using PathClause = Clause<ClauseKind::Path>;
using TypeClause = Clause<ClauseKind::Type>;
using MeshClause = Clause<ClauseKind::Mesh>;
using DrawClause = Clause<ClauseKind::Draw, 2, 2>;
using PreClause = ParameterClause<ClauseKind::Pre>;
using PostClause = ParameterClause<ClauseKind::Post>;
using AppendClause = ParameterClause<ClauseKind::Append>;
using PrependClause = ParameterClause<ClauseKind::Prepend>;
using ShadersClause = ParameterClause<ClauseKind::Prepend>;

std::ostream &operator<<(std::ostream &os, const vp::ClauseKind &kind);

} // namespace vp

template <>
struct fmt::formatter<vp::ClauseKind> : ostream_formatter {};

#endif // VP_INTERPRETER_CLAUSE_HPP
