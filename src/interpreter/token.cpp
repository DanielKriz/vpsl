#include <vp/interpreter/token.hpp>

#include <fmt/core.h>
#include <fmt/ostream.h>

namespace vp {

Token::Token(std::string lexeme, TokenKind kind, u64 line)
    : m_lexeme(std::move(lexeme)), m_tokenKind(kind), m_line(line) {};

Token::Token(TokenKind kind) : Token("", kind, 0) {};

TokenKind Token::getTokenKind() const noexcept {
    return m_tokenKind;
}

u64 Token::getLineNumber() const noexcept {
    return m_line; 
}

const std::string &Token::getLexeme() const noexcept {
    return m_lexeme; 
}

std::ostream &operator<<(std::ostream &os, const vp::Token &token) {
    const auto repr = fmt::format(
        "Token({}, {}, '{}')",
        token.m_line,
        token.m_tokenKind,
        token.m_lexeme
    );
    return os << repr;
}

} // namespace vp
