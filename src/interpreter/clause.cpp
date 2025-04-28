#include <vp/interpreter/clause.hpp>

namespace vp {

bool ClauseBase::isValidClause(TokenIterator &it, const TokenIterator &end) const noexcept {
    u64 parametersCount = 0;

    if (it->getTokenKind() != static_cast<TokenKind>(getKind())) {
        return false;
    }
    ++it;

    if (it->getTokenKind() != TokenKind::LeftParen) {
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
