#ifndef VP_INTERPRETER_INTERPRETER_HPP
#define VP_INTERPRETER_INTERPRETER_HPP

#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>

#include <vp/interpreter/lexer.hpp>
#include <vp/interpreter/token.hpp>
#include <vp/interpreter/parser.hpp>
#include <vp/interpreter/directive.hpp>
#include <vp/error_handling.hpp>
#include <vp/shader_code_store.hpp>
#include <vp/builder_graph/objects/shader_object.hpp>

namespace vp {

class Interpreter final {
public:
    explicit Interpreter(const std::string &src);
    explicit Interpreter(std::ifstream &fin);

    // TODO: return builder graph
    void interpret();

private:

    std::istringstream m_stringStream;
    std::istream m_inputStream;
    ShaderCodeStore m_store;
};

} // namespace vp

#endif // VP_INTERPRETER_INTERPRETER_HPP
