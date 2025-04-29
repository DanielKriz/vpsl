#ifndef VP_INTERPRETER_DIRECTIVES_INTERFACE_HPP
#define VP_INTERPRETER_DIRECTIVES_INTERFACE_HPP

#include <memory>
#include <set>

#include <vp/interpreter/clause.hpp>

namespace vp {

using ClauseSet = std::set<std::unique_ptr<IClause>>;

class IDirective {
public:
    virtual ~IDirective() = default;
#if 0
    [[nodiscard]] virtual const ClauseSet &getClauses() const noexcept = 0;
#endif
    [[nodiscard]] virtual bool areClausesCorrect(
        TokenIterator &it,
        const TokenIterator &end
    ) = 0;
};

} // namespace vp

#endif // VP_INTERPRETER_DIRECTIVES_INTERFACE_HPP
