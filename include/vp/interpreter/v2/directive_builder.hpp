#ifndef VP_INTERPRETER_DIRECTIVES_V2_HPP
#define VP_INTERPRETER_DIRECTIVES_V2_HPP

#include <vp/interpreter/clause.hpp>

#include <vector>
#include <memory>

namespace v2 {

class DirectiveBuilder {
public:
    template <typename T>
    DirectiveBuilder &&addClause();
private:
    std::vector<std::unique_ptr<vp::IClause>> m_clauses;
};

class Directive {
public:
private:
};

namespace directive {

Directive shaderDirectiveClone() {
}

} // namespace directive

} // namespace vp

#endif //  VP_INTERPRETER_DIRECTIVES_V2_HPP
