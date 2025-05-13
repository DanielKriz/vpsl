#ifndef VP_INTERPRETER_TOKEN_HPP
#define VP_INTERPRETER_TOKEN_HPP

#include <iosfwd>
#include <string>

#include <vp/interpreter/token_kind.hpp>
#include <vp/types.hpp>
#include <vp/utils.hpp>

#include <fmt/ostream.h>

namespace vp {

class Token final {
public:
    Token() = default;
    Token(std::string lexeme, TokenKind kind, u64 line);

    [[nodiscard]] TokenKind getTokenKind() const noexcept;
    [[nodiscard]] u64 getLineNumber() const noexcept;
    [[nodiscard]] const std::string &getLexeme() const noexcept;

#if 0
    friend std::ostream &operator<<(std::ostream &os, const Token &token) {
        const auto repr = fmt::format(
            "Token({}, {}, '{}')",
            token.m_line,
#if 0
            token.m_tokenKind,
#else
            "something",
#endif
            token.m_lexeme
        );
        return os << repr;
    }
#else
    friend std::ostream &operator<<(std::ostream &os, const Token &token);
#endif

private:

    std::string m_lexeme;
    TokenKind m_tokenKind { TokenKind::Unknown };
    u64 m_line { 0 };
};

} // namespace vp

template <>
struct fmt::formatter<vp::Token> : ostream_formatter {};

#endif // VP_INTERPRETER_TOKEN_HPP
