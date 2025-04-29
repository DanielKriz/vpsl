#pragma once
#include <regex>
#include <string>
#include <vector>
#include <limits>

#include <vp/types.hpp>
#include <vp/utils.hpp>
#include <vp/interpreter/token.hpp>

namespace vp {

class Lexer final {
public:

    using Iterator = std::string::const_iterator;

#if 0
    Lexer() = default;
#else
    Lexer() : m_currentLine(0), m_buffer() {
        m_buffer.reserve(std::numeric_limits<u8>::max());
    }
#endif

    std::optional<std::vector<Token>> scan(const std::string &input);

    static std::string &joinLines(std::string &dst, const std::string &src) {
        utils::trim(dst);
        // remove the \\ from the string
        dst.pop_back();
        utils::trim(dst);
        dst += " " + utils::trimCopy(src);
        return dst;
    }

    [[nodiscard]] inline static bool isContinuous(const std::string &line) {
        static std::regex re(R"(.*\\\s*)");
        return std::regex_match(line, re);
    }

    [[nodiscard]] inline static bool isDirective(const std::string &line) {
        static std::regex re(R"(\s*#pragma\s+vp\s+.*)");
        return std::regex_match(line, re);
    }

    [[nodiscard]] inline static bool isSeparator(const char ch) {
        switch (ch) {
        case '(':
        case ')':
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            return true;
        default:
           return false;
        }
    }

    [[nodiscard]] static TokenKind mapTokenKind(const std::string &str) {
        auto tokenKind = utils::mapStringToEnumKind<TokenKind>(str);
        return tokenKind.has_value() ? *tokenKind : TokenKind::Identifier;
    }

private:
    void getWholeIdentifier(Iterator &it, const Iterator &end);

    u64 m_currentLine;
    std::string m_buffer;
};

} // namespace vp
