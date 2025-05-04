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

    ShaderObject globalShaderObject = ShaderObject{};
    ShaderObject *pCurrentShaderObject = &globalShaderObject;
    ProgramObject currentProgram;

    m_stage = vp::ParserStage::ComposingGlobalScope;

    while (std::getline(m_inputStream, line)) {
        /// 1. Lexer tokenizes the line
        /// 2. Parser checks whether it is a valid directive and returns it
        /// 3. Interpreter checks whether the GLSL code contains everything important

        if (Lexer::isContinuous(line)) {
            std::string tmp;
            std::getline(m_inputStream, tmp);
            Lexer::joinLines(line, tmp);
        }

        std::optional<std::vector<Token>> tokens = lexer.scan(line);
        if (not tokens.has_value() or tokens->empty()) {
            continue;
        }

        const auto directiveToken = *tokens->cbegin();

        if (directiveToken.getTokenKind() == TokenKind::SourceLine) {
            if (m_stage == vp::ParserStage::ComposingShader) {
                pCurrentShaderObject->addLine(directiveToken.getLexeme());
                continue;
            }
            globalShaderObject.addLine(directiveToken.getLexeme());
            continue;
        }
#if 0
        utils::debug::printVector(*tokens, " -> ");
#endif

        // Remove the directive token, because it is not going to be needed further
        tokens->erase(tokens->begin());
        const auto &clauseTokens = *tokens;

        std::unique_ptr<IDirective> pDirective = nullptr;
        pDirective = Parser::constructDirectiveFromToken(directiveToken);
        pDirective->populate(clauseTokens);

        if (pDirective == nullptr) {
            throw std::runtime_error("There some problem with memory");
        }

        if (pDirective->getDirectiveKind() == DirectiveKind::Shader) {
            auto * pDir = dynamic_cast<ShaderDirective *>(pDirective.get());
            setCurrentStage(vp::ParserStage::ComposingShader);
#if 1
            if (not pCurrentShaderObject->isEmpty()) {
                fmt::println("{}", fmt::styled("Current Shader Object:", fmt::fg(fmt::color::red)));
                fmt::println("{}", fmt::styled("----------------------", fmt::fg(fmt::color::red)));
                std::cout << *pCurrentShaderObject << std::endl;
            }
#endif
            std::cout << pDir->getName() << std::endl;
            if (pDir->getName().empty()) {
                pCurrentShaderObject = m_store.emplaceUnnamed();
            } else {
                pCurrentShaderObject = m_store.emplace(pDir->getName());
            }
            pCurrentShaderObject->appendLines(globalShaderObject);

#if 1
            for (const std::string &shader : pDir->getAppendSet()) {
                pCurrentShaderObject->addToAppendSet(*(m_store[shader]));
            }

            for (const std::string &shader : pDir->getPrependSet()) {
                pCurrentShaderObject->addToPrependSet(*(m_store[shader]));
            }
#endif
        } else if (pDirective->getDirectiveKind() == DirectiveKind::Program) {
            setCurrentStage(vp::ParserStage::ComposingProgram);
        } else if (pDirective->getDirectiveKind() == DirectiveKind::Begin) {
            m_scope.push(m_stage);
        } else if (pDirective->getDirectiveKind() == DirectiveKind::End) {
            if (m_scope.empty()) {
                throw std::runtime_error("Out of scope");
            }
            m_scope.pop();
            if (m_stage == vp::ParserStage::ComposingShader) {
                m_stage = vp::ParserStage::ComposingProgram;
            } else if (m_stage == vp::ParserStage::ComposingProgram) {
                m_stage = vp::ParserStage::ComposingGlobalScope;
            }
        } else if (pDirective->getDirectiveKind() == DirectiveKind::Load) {
        }

        fmt::println("End of iteration");
    }


#if 1
    fmt::println("{}", fmt::styled("Global Shader Object:", fmt::fg(fmt::color::blue)));
    fmt::println("{}", fmt::styled("---------------------", fmt::fg(fmt::color::blue)));
    std::cout << globalShaderObject << std::endl;
    fmt::println("");
    fmt::println("{}", fmt::styled("Latest Shader Object:", fmt::fg(fmt::color::blue)));
    fmt::println("{}", fmt::styled("---------------------", fmt::fg(fmt::color::blue)));
    std::cout << *pCurrentShaderObject << std::endl;
#endif

#if 1
    m_store.getShaderObject("main_vs")->compose();
    m_store.getShaderObject("main_fs")->compose();

    fmt::println("{}", fmt::styled("Vertex Shader Object:", fmt::fg(fmt::color::purple)));
    fmt::println("{}", fmt::styled("---------------------", fmt::fg(fmt::color::purple)));
    std::cout << *m_store.getShaderObject("main_vs") << std::endl;
    fmt::println("{}", fmt::styled("Fragment Shader Object:", fmt::fg(fmt::color::purple)));
    fmt::println("{}", fmt::styled("-----------------------", fmt::fg(fmt::color::purple)));
    std::cout << *m_store.getShaderObject("main_fs") << std::endl;
#endif

    if (not m_scope.empty()) {
        ErrorHandler::report<std::runtime_error>(1, "Invalid scope");
    }
    std::cout << "interpretation is finished" << std::endl;
}

} // namespace vp
