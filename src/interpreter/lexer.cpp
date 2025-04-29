#include <vp/interpreter/lexer.hpp>

#include <iostream>
#include <re2/re2.h>

namespace vp {

std::optional<std::vector<Token>> Lexer::scan(const std::string &input) {
    std::vector<Token> tokens;

    m_currentLine++;

    // There is nothing to scan
    if (utils::trimCopy(input).empty()) {
        return {};
    }

    if (not isDirective(input)) {
        // TODO: what to do when empty
        tokens.emplace_back(input, TokenKind::SourceLine, m_currentLine);
        return tokens;
    }

    RE2 re{R"(\s*#pragma\s+vp\s+(.*))", RE2::CannedOptions::DefaultOptions};
    std::string line;
    RE2::PartialMatch(input, re, &line);

    // at this point we know that at the start of the line there is correctly
    // put '#pragma vp'

    for (auto it = line.cbegin(); it != line.cend(); ++it) {
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
        getWholeIdentifier(it, line.cend());

        if (m_buffer == "//") {
            // Comment encountered
            break;
        }

        if (m_buffer == "pragma" or m_buffer == "vp") {
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
