#ifndef VP_INTERPRETER_BASE_DIRECTIVE_HPP
#define VP_INTERPRETER_BASE_DIRECTIVE_HPP

#include <map>
#include <memory>
#include <unordered_set>
#include <iostream>

#include <vp/interpreter/directives/directive_interface.hpp>

namespace vp {

class DirectiveBase : public IDirective {
public:
    DirectiveBase(std::initializer_list<TokenKind> kinds) {
        for (const auto kind : kinds) {
            addClause(kind);
        }
    }

#if 0
    [[nodiscard]] const ClauseSet &getClauses() const noexcept override {
        return clauses;
    }
#endif
    [[nodiscard]] bool populateClauses(const std::vector<Token> &tokens) override {
        std::vector<TokenIterator> clausePositions;
        for (auto it = tokens.begin(); it != tokens.end(); ++it) {
            if (clauses.contains(it->getTokenKind())) {
                clausePositions.push_back(it);
            }
        }

        for (auto &clausePos : clausePositions) {
            if (m_closed.contains(clausePos->getTokenKind())) {
                return false;
            }

            auto &clause = clauses.find(clausePos->getTokenKind())->second;

            if (clause->isValidClause(clausePos, tokens.end())) {
                clause->populate(clausePos, tokens.end());
                m_closed.insert(clausePos->getTokenKind());
            } else {
                return false;
            }
        }

        return false;
    }

    [[nodiscard]] bool areClausesCorrect(TokenIterator &it, const TokenIterator &end) override {
        while (it != end) {
            auto itCopy = it;
            if (auto clause = clauses.find(it->getTokenKind()); clause != clauses.end()) {
                if (not clause->second->isValidClause(it, end)) {
                    return false;
                }
                clause->second->populate(itCopy, end);
                clauses.erase(clause->first);
            } else {
                return false;
            }
        }
        return true;
    }

    void populate(const std::vector<Token> &tokens) override = 0;

protected:

    void populateData(TokenKind kind, std::string &str) {
        if (auto *clause = getClause(kind); clause != nullptr) {
            if (clause->isPopulated()) {
                std::string tmp { clause->getParameters()[0] };
                str = std::move(tmp);
            }
        }
    }

    void populateData(TokenKind kind, std::unordered_set<std::string_view> &set) {
        if (auto *clause = getClause(kind); clause != nullptr) {
            if (clause->isPopulated()) {
                std::ranges::for_each(clause->getParameters(), [&set](const auto &it) {
                    set.insert(it);
                });
            }
        }
    }

    template <typename T>
    void populateData(TokenKind kind, T &value) {
        if (auto *clause = getClause(kind); clause != nullptr) {
            if (clause->isPopulated()) {
                value = *utils::mapStringToEnumKind<T>(clause->getParameters()[0]);
            }
        }
    }


    const std::unordered_set<TokenKind> &getClauseKinds() const noexcept {
        return m_clauseKinds;
    }

    void addClause(TokenKind kind) {
        using enum TokenKind;
        switch (kind) {
        case Name:
            clauses.insert({Name, std::make_unique<NameClause>()});
            break;
        case Type:
            clauses.insert({Type, std::make_unique<TypeClause>()});
            break;
        case Prepend:
            clauses.insert({Prepend, std::make_unique<PrependClause>()});
            break;
        case Append:
            clauses.insert({Append, std::make_unique<AppendClause>()});
            break;
        case Pre:
            clauses.insert({Pre, std::make_unique<PreClause>()});
            break;
        case Post:
            clauses.insert({Post, std::make_unique<PostClause>()});
            break;
        default:
            break;
        }
    }

private:
    IClause * getClause(TokenKind kind) {
        auto clause = clauses.find(kind);
        return clause == clauses.end() ? nullptr : clause->second.get();
    }

    std::map<TokenKind, std::unique_ptr<IClause>> clauses;
    std::unordered_set<TokenKind> m_closed;
    std::unordered_set<TokenKind> m_clauseKinds;
};

} // namespace vp

#endif // VP_INTERPRETER_BASE_DIRECTIVE_HPP
