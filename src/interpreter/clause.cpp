#include <vp/interpreter/clause.hpp>
#include <vp/error_handling.hpp>

#include <iostream>

namespace vp {

bool ClauseBase::isValidClause(TokenIterator &it, const TokenIterator &end) const noexcept {
    u64 parametersCount = 0;

    if (it->getTokenKind() != static_cast<TokenKind>(getKind())) {
        ErrorHandler::warn(0, fmt::format("Wrong clause type: '{}'", it->getLexeme()));
        return false;
    }
    ++it;

    if (it->getTokenKind() != TokenKind::LeftParen) {
        ErrorHandler::warn(0, "Missing left parenthesis for a clause");
        return false;
    }
    ++it;

    bool isExpectingParameter = true;
    while (it->getTokenKind() != TokenKind::RightParen and it != end) {
        switch (it->getTokenKind()) {
        case TokenKind::Identifier:
            isExpectingParameter = false;
            ++parametersCount;
            break;
        case TokenKind::Comma:
            isExpectingParameter = true;
            break;
        default:
            std::cout << *it << std::endl;
            ErrorHandler::warn(0, "Wrong type of token inside a clause");
            return false;
        }
        ++it;
    }

    if (isExpectingParameter) {
        ErrorHandler::warn(0, "Missing parameter");
        return false;
    }

    if (parametersCount < getMinParameters() or parametersCount > getMaxParameters()) {
        ErrorHandler::warn(0, "Unsupported number of arguments");
        return false;
    }

    if (it != end) {
        ++it;
    }

    return true;
}

bool ClauseBase::isValidClause(const std::vector<Token> &tokens) const noexcept {
    u64 parametersCount = 0;
    auto it = tokens.cbegin();

    if (it->getTokenKind() != static_cast<TokenKind>(getKind())) {
        return false;
    }
    ++it;

    if (it->getTokenKind() != TokenKind::LeftParen) {
        return false;
    }
    ++it;

    bool isExpectingParameter = true;
    while (it->getTokenKind() != TokenKind::RightParen and it != tokens.cend()) {
        switch (it->getTokenKind()) {
        case TokenKind::Identifier:
            isExpectingParameter = false;
            ++parametersCount;
            break;
        case TokenKind::Comma:
            isExpectingParameter = true;
            break;
        default:
            return false;
        }
        ++it;
    }

    if (isExpectingParameter) {
        return false;
    }

    if (parametersCount < getMinParameters() or parametersCount > getMaxParameters()) {
        return false;
    }

    return true;
}

} // namespace vp
