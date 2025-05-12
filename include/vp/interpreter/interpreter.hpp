#ifndef VP_INTERPRETER_INTERPRETER_HPP
#define VP_INTERPRETER_INTERPRETER_HPP

#include <fstream>
#include <iostream>
#include <sstream>

#include <vp/description/shader_code.hpp>
#include <vp/error_handling.hpp>
#include <vp/interpreter/directive.hpp>
#include <vp/interpreter/lexer.hpp>
#include <vp/interpreter/parser.hpp>
#include <vp/interpreter/token.hpp>

namespace vp {

class Interpreter final {
public:
    explicit Interpreter(const std::string &src);
    explicit Interpreter(std::ifstream &fin);

    std::vector<desc::ProgramDescription> interpret();

private:
    std::istringstream m_stringStream;
    std::istream m_inputStream;
};

} // namespace vp

#endif // VP_INTERPRETER_INTERPRETER_HPP
