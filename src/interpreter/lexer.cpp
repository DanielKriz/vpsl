#include <vp/interpreter/lexer.hpp>

#include <iostream>

namespace vp {

std::optional<std::vector<Token>> Lexer::scan(const std::string &input) {
    std::vector<Token> tokens;

    m_currentLine++;
    if (not isDirective(input)) {
        // TODO: what to do when empty
        tokens.emplace_back(input, TokenKind::SourceLine, m_currentLine);
        return tokens;
    }

    for (auto it = input.cbegin(); it != input.cend(); ++it) {
        if (static_cast<bool>(std::isspace(*it))) {
            continue;
        }

        switch (*it) {
        case '(': 
            tokens.emplace_back("(", TokenKind::LeftParen, m_currentLine);
            continue;
        case ')':
            tokens.emplace_back(")", TokenKind::RightParen, m_currentLine);
            continue;
        case '{': 
            tokens.emplace_back("{", TokenKind::LeftBracket, m_currentLine);
            continue;
        case '}':
            tokens.emplace_back("}", TokenKind::RightBracket, m_currentLine);
            continue;
        case ',':
            tokens.emplace_back(",", TokenKind::Comma, m_currentLine);
            continue;
        }

        m_buffer.clear();
        getWholeIdentifier(it, input.cend());

        if (m_buffer == "//") {
            // Comment encountered
            break;
        }

        tokens.emplace_back(m_buffer, mapTokenKind(m_buffer), m_currentLine);
        std::cout << "Currently emplaced: " << tokens.back() << std::endl;
    }
    return tokens;
}

void Lexer::getWholeIdentifier(Iterator &it, const Iterator &end) {
    while (not isSeparator(*it) and it != end) {
        m_buffer += *it;
        ++it;
    }
    --it;
}

} // namespace vp
