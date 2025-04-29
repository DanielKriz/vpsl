#include "vp/dependency_graph.hpp"
#include <vp/interpreter/interpreter.hpp>

namespace vp {

Interpreter::Interpreter(const std::string &src)
    : m_stringStream(src),
    m_inputStream(m_stringStream.rdbuf()) { }

Interpreter::Interpreter(std::ifstream &fin)
    : m_inputStream(fin.rdbuf()) { }

void Interpreter::interpret() {
    fmt::println("Starting the interpreter");
    Lexer lexer{};
    Parser parser{};

    std::string line{};
    bool isExpectingNewScope = false;
    bool startedANewScope = false;

    while (std::getline(m_inputStream, line)) {
        /// 1. Lexer tokenizes the line
        /// 2. Parser checks whether it is a valid directive and returns it
        /// 3. Interpreter checks whether the GLSL code contains everything important

        if (Lexer::isContinuous(line)) {
            std::cout << "Line is in fact continuous" << std::endl;
            std::string tmp;
            std::getline(m_inputStream, tmp);
            Lexer::joinLines(line, tmp);
        }

        std::optional<std::vector<Token>> tokens = lexer.scan(line);
        if (not tokens.has_value() or tokens->empty()) {
            continue;
        }

        const auto directiveToken = *tokens->cbegin();
        // Remove the directive token, because it is not going to be needed further
        tokens->erase(tokens->begin());
        const auto &clauseTokens = *tokens;
#if 0
        std::cout << "Begin -- List of current tokens:" << std::endl;
        for (const auto &token : *tokens) {
            std::cout << token << std::endl;
        }
        std::cout << "END -- List of current tokens:" << std::endl;
#endif

        std::unique_ptr<IDirective> pDirective = nullptr;

        switch (directiveToken.getTokenKind()) {
        case vp::TokenKind::ShaderDirective:
            setCurrentStage(vp::ParserStage::ComposingShader);
            {
                pDirective = std::make_unique<ShaderDirective>();
                isExpectingNewScope = true;
            }
            break;
        case vp::TokenKind::ProgramDirective:
            setCurrentStage(vp::ParserStage::ComposingProgram);
            {
                pDirective = std::make_unique<ProgramDirective>();
            }
            break;
        case vp::TokenKind::LoadDirective:
            break;
        case vp::TokenKind::BeginDirective:
            m_scope.push(m_stage);
            break;
        case vp::TokenKind::EndDirective:
            if (m_scope.empty()) {
                throw std::runtime_error("Out of scope");
            }
            m_scope.pop();
            break;
        default:
            break;
        }

        if (pDirective != nullptr) {
            pDirective->populate(clauseTokens);
            if (auto * pDir = dynamic_cast<ShaderDirective *>(pDirective.get())) {
                fmt::println("name of shader is '{}'", pDir->getName());
                fmt::println("type of shader is '{}'", static_cast<u32>(pDir->getType()));
                for (const auto &dep : pDir->getPrependSet()) {
                    fmt::println("\tPrepend dep: {}", dep);
                }
                for (const auto &dep : pDir->getAppendSet()) {
                    fmt::println("\tAppend dep: {}", dep);
                }
            }
        }
    }

    if (not m_scope.empty()) {
        ErrorHandler::report<std::runtime_error>(1, "Invalid scope");
    }
    std::cout << "interpretation is finished" << std::endl;
}

} // namespace vp
