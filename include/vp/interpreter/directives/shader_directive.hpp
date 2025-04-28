#ifndef VP_INTERPRETER_DIRECTIVE_SHADER_HPP
#define VP_INTERPRETER_DIRECTIVE_SHADER_HPP

#include <map>
#include <memory>

#include <vp/interpreter/clause.hpp>
#include <vp/interpreter/token.hpp>
#include <vp/interpreter/directives/directive_interface.hpp>
#include <vp/types.hpp>

namespace vp {

class ShaderDirective : public IDirective {
public:
    ShaderDirective() {
        clauses.insert({TokenKind::Name, std::make_unique<NameClause>()});
        clauses.insert({TokenKind::Type, std::make_unique<TypeClause>()});
        clauses.insert({TokenKind::Prepend, std::make_unique<PrependClause>()});
        clauses.insert({TokenKind::Append, std::make_unique<AppendClause>()});
    }

    [[nodiscard]] const ClauseSet &getClauses() const noexcept override {
        return {};
    }

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

private:
    std::map<TokenKind, std::unique_ptr<IClause>> clauses;
};

} // namespace vp

#endif // VP_INTERPRETER_DIRECTIVE_SHADER_HPP
