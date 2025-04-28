#include "vp/interpreter/clause.hpp"
#include "vp/interpreter/directive.hpp"
#include "vp/interpreter/directives/directive_interface.hpp"
#include <vp/interpreter/interpreter.hpp>
#include <span>

namespace vp {

Interpreter::Interpreter(const std::string &src)
    : m_stringStream(src),
    m_inputStream(m_stringStream.rdbuf()) { }

Interpreter::Interpreter(std::ifstream &fin)
    : m_inputStream(fin.rdbuf()) { }

void Interpreter::interpret() {
    fmt::println("Starting the interpreter");
    Lexer lexer{};

    std::string line{};
    while (std::getline(m_inputStream, line)) {
        /// 1. Lexer tokenizes the line
        /// 2. Parser checks whether it is a valid directive and returns it
        /// 3. Interpreter checks whether the GLSL code contains everything important

        auto tokens = lexer.scan(line);
        if (not tokens.has_value() or tokens->empty()) {
            continue;
        }

        if (auto firstToken = tokens.value()[0]; firstToken.getTokenKind() == TokenKind::SourceLine) {
            fmt::println("Source line '{}' on line no. {}", firstToken.getLexeme(), firstToken.getLineNumber());
            if (firstToken.getLexeme() == "") {
                continue;
            }
        }

        // Checking if correct start

        auto it = tokens->cbegin();

        std::cout << *it << std::endl;
        if (it->getTokenKind() != TokenKind::Pragma or (++it)->getTokenKind() != TokenKind::Namespace) {
            throw std::runtime_error("Prefix is not valid");
        }

        std::cout << *it << std::endl;

        for (const auto &token : *tokens) {
            std::cout << token << std::endl;
        }

        std::unique_ptr<IDirective> pDirective;

        switch ((++it)->getTokenKind()) {
        case vp::TokenKind::ShaderDirective:
            setCurrentStage(vp::ParserStage::ComposingShader);
            {
                pDirective = std::make_unique<ShaderDirective>();
            }
            break;
        case vp::TokenKind::ProgramDirective:
            setCurrentStage(vp::ParserStage::ComposingProgram);
            break;
        case vp::TokenKind::LoadDirective:
            break;
        case vp::TokenKind::BeginDirective:
            m_scope.push(m_stage);
            break;
        case vp::TokenKind::EndDirective:
            m_scope.pop();
            break;
        default:
            break;
        }

        // if ((++it)->getTokenKind() != TokenKind::ShaderDirective) {
        //     continue;
        // }

        ++it;
        auto ret = pDirective->areClausesCorrect(it, tokens->cend());

        std::cout << "Result of clause thingy" << std::endl;
        std::cout << "Are clauses correct: " << std::boolalpha << ret << std::endl;
        std::cout << *it << std::endl;

        if (not m_scope.empty()) {
            // there is some unfinished scope => Error
        }
    }
}

} // namespace vp
