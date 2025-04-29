#ifndef VP_INTERPRETER_BASE_DIRECTIVE_HPP
#define VP_INTERPRETER_BASE_DIRECTIVE_HPP

#include <map>
#include <memory>
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

    [[nodiscard]] bool areClausesCorrect(TokenIterator &it, const TokenIterator &end) override {
        while (it != end) {
            if (auto clause = clauses.find(it->getTokenKind()); clause != clauses.end()) {
                if (not clause->second->isValidClause(it, end)) {
                    return false;
                }
                clauses.erase(clause->first);
            } else {
                return false;
            }
        }
        return true;
    }

protected:
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
    std::map<TokenKind, std::unique_ptr<IClause>> clauses;
};

} // namespace vp

#endif // VP_INTERPRETER_BASE_DIRECTIVE_HPP
