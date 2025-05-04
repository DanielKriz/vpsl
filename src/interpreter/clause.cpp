#include <vp/interpreter/clause.hpp>
#include <vp/error_handling.hpp>

#include <iostream>

namespace vp {

bool IClause::isClause(const Token &token) noexcept {
    return isClause(token.getTokenKind());
}

bool IClause::isClause(TokenKind kind) noexcept {
    using enum TokenKind;
    switch (kind) {
    case Name:
    case Type:
    case Pre:
    case Post:
    case Prepend:
    case Append:
        return true;
    default:
        return false;
    }
}

// There is no need to check whether the clauses is correct, because this
// function shouldn't be called without the first call to the isValid function.
void ClauseBase::populate(const std::vector<Token> &tokens) {
    for (const auto &token : tokens) {
        if (token.getTokenKind() == TokenKind::Identifier) {
            m_parameters.push_back(token.getLexeme());
        }
    }
}

void ClauseBase::populate(TokenIterator it, const TokenIterator &end) {
    while (it->getTokenKind() != TokenKind::RightParen or it != end) {
        if (it->getTokenKind() == TokenKind::Identifier) {
            m_parameters.push_back(it->getLexeme());
        }
        ++it;
    }
    m_populated = true;
}

bool ClauseBase::isValidClause(TokenIterator it, const TokenIterator &end) const {
    u64 parametersCount = 0;

    if (it->getTokenKind() != static_cast<TokenKind>(getKind())) {
        throw std::runtime_error(fmt::format("Wrong clause type: '{}'", it->getLexeme()));
        return false;
    }
    ++it;

    if (it->getTokenKind() != TokenKind::LeftParen) {
        throw std::runtime_error("Missing left parenthesis for a clause");
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
            throw std::runtime_error("Wrong type of token inside a clause");
            return false;
        }
        ++it;
    }

    if (isExpectingParameter) {
        throw std::runtime_error("Missing parameter");
        return false;
    }

    if (parametersCount < getMinParameters() or parametersCount > getMaxParameters()) {
        throw std::runtime_error("Unsupported number of arguments");
        return false;
    }

    if (it != end) {
        ++it;
    }

    return true;
}

bool ClauseBase::isValidClause(const std::vector<Token> &tokens) const {
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
