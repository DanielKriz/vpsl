#include <vp/interpreter/interpreter.hpp>

namespace vp {

Interpreter::Interpreter(const std::string &src)
    : m_stringStream(src),
    , m_inputStream(m_stringStream.rdbuf()) 
    {
    // So that the application is in defined state
    desc::ShaderCodeStore::getInstance().clear();
}

Interpreter::Interpreter(std::ifstream &fin)
    : m_inputStream(fin.rdbuf()) {}

#if 1
std::vector<desc::ProgramDescription> Interpreter::interpret() {
#else
void Interpreter::interpret() {
#endif
    fmt::println("Starting the interpreter");
    Lexer lexer{};
    Parser parser{};

    std::string line{};

    desc::ShaderCodeStore &store = desc::ShaderCodeStore::getInstance();

    ShaderCode globalShaderCode = ShaderCode{};
    ShaderCode *pCurrentShaderCode = &globalShaderCode;
    desc::ProgramDescriptionBuilder programBuilder;

    bool isLastDirectiveShader = false;

    while (std::getline(m_inputStream, line)) {
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
            if (parser.peekScope() == ParserScope::Global) {
                globalShaderCode.addLine(directiveToken.getLexeme());
            } else if (parser.peekScope() == ParserScope::Program) {
                throw std::runtime_error("There cannot be a lone statement in program scope");
            } else {
                pCurrentShaderCode->addLine(directiveToken.getLexeme());
            }
            continue;
        }

        // Remove the directive token, because it is not going to be needed further
        tokens->erase(tokens->begin());
        const auto &clauseTokens = *tokens;

        auto directive = Parser::createDirectiveFromToken(directiveToken);
        if (not directive.has_value()) {
            throw std::runtime_error("No directive was created");
        }

        directive->populateClauses(clauseTokens);

        DirectiveKind directiveKind = directive->getDirectiveKind();
        if (directiveKind == DirectiveKind::Shader) {
#if 0
            if (not pCurrentShaderObject->isEmpty()) {
                fmt::println("{}", fmt::styled("Current Shader Object:", fmt::fg(fmt::color::red)));
                fmt::println("{}", fmt::styled("----------------------", fmt::fg(fmt::color::red)));
                std::cout << *pCurrentShaderObject << std::endl;
            }
#endif

            auto name = directive->getParameter<ClauseKind::Name>();
            if (name.has_value() and not name->empty()) {
                if (parser.peekScope() == ParserScope::Global) {
                    name = "global:" + *name;
                } else {
                    name = programBuilder.createShaderName(*name);
                }
                pCurrentShaderCode = store.emplace(*name);
            } else {
                pCurrentShaderCode = store.emplaceUnnamed();
            }

            auto type = directive->getParameter<ShaderCodeKind>();
            if (type.has_value()) {
                pCurrentShaderCode->setKind(*type);
            } else {
                pCurrentShaderCode->setKind(ShaderCodeKind::Generic);
            }

            // add the shader to the program
            if (parser.peekScope() != ParserScope::Global) {
                programBuilder.addShaderCode(*pCurrentShaderCode);
            }

            // Do this later
#if 0
            auto prependSet = directive->getParameters<ClauseKind::Prepend>();
            if (prependSet.has_value()) {
                for (const auto &shader : *prependSet) {
                    pCurrentShaderObject->addToPrependSet(*m_store[shader]);
                }
            }

            auto appendSet = directive->getParameters<ClauseKind::Prepend>();
            if (appendSet.has_value()) {
                for (const auto &shader : *prependSet) {
                    pCurrentShaderObject->addToAppendSet(*m_store[shader]);
                }
            }
#endif

            pCurrentShaderCode->appendLines(globalShaderCode);
            isLastDirectiveShader = true;
        } else if (directiveKind == DirectiveKind::Program) {
            auto name = directive->getParameter<ClauseKind::Name>();
            if (name.has_value()) {
                programBuilder.setName(*name);
            } else {
                programBuilder.setNameFromID();
            }
            isLastDirectiveShader = false;
        } else if (directiveKind == DirectiveKind::Load) {
            isLastDirectiveShader = false;
        } else if (directiveKind == DirectiveKind::Begin) {
            if (isLastDirectiveShader and parser.peekScope() == ParserScope::Global) {
                parser.pushGlobalShaderScope();
            } else {
                parser.pushScope();
            }
            isLastDirectiveShader = false;
        } else if (directiveKind == DirectiveKind::End) {
            if (parser.peekScope() == ParserScope::Program) {
                parser.addProgramDescription(programBuilder.build());
                programBuilder.reset();
            }
            parser.popScope();
            isLastDirectiveShader = false;
        } else {
            throw std::runtime_error("Unknown Directive kind!");
        }
#if 0
        fmt::println("finished iteration");
#endif
    }

    // std::cout << m_store << std::endl;

#if 0
    fmt::println("{}", fmt::styled("Global Shader Object:", fmt::fg(fmt::color::blue)));
    fmt::println("{}", fmt::styled("---------------------", fmt::fg(fmt::color::blue)));
    std::cout << globalShaderObject << std::endl;
    fmt::println("");
    fmt::println("{}", fmt::styled("Latest Shader Object:", fmt::fg(fmt::color::blue)));
    fmt::println("{}", fmt::styled("---------------------", fmt::fg(fmt::color::blue)));
    std::cout << *pCurrentShaderObject << std::endl;
#endif

#if 1
    store.getShaderCode("main:main_vs")->compose();
    store.getShaderCode("main:main_fs")->compose();

    fmt::println("{}", fmt::styled("Vertex Shader Object:", fmt::fg(fmt::color::purple)));
    fmt::println("{}", fmt::styled("---------------------", fmt::fg(fmt::color::purple)));
    std::cout << *store.getShaderCode("main:main_vs") << std::endl;
    fmt::println("{}", fmt::styled("Fragment Shader Object:", fmt::fg(fmt::color::purple)));
    fmt::println("{}", fmt::styled("-----------------------", fmt::fg(fmt::color::purple)));
    std::cout << *store.getShaderCode("main:main_fs") << std::endl;
    fmt::println("{}", fmt::styled("Included Shader Object:", fmt::fg(fmt::color::purple)));
    fmt::println("{}", fmt::styled("-----------------------", fmt::fg(fmt::color::purple)));
    std::cout << *store.getShaderCode("global:included") << std::endl;
    std::cout << std::endl;
    fmt::println("{}", fmt::styled("Vertex Shader Object:", fmt::fg(fmt::color::purple)));
    fmt::println("{}", fmt::styled("---------------------", fmt::fg(fmt::color::purple)));
    std::cout << *store.getShaderCode("the_second:main_vs") << std::endl;
    fmt::println("{}", fmt::styled("Fragment Shader Object:", fmt::fg(fmt::color::purple)));
    fmt::println("{}", fmt::styled("-----------------------", fmt::fg(fmt::color::purple)));
    std::cout << *store.getShaderCode("the_second:main_fs") << std::endl;
#endif

#if 0
    fmt::println("{}", fmt::styled("Current Program Shaders:", fmt::fg(fmt::color::green)));
    fmt::println("{}", fmt::styled("------------------------", fmt::fg(fmt::color::green)));
    std::cout << currentProgram << std::endl;
    fmt::println("{}", fmt::styled("------------------------", fmt::fg(fmt::color::green)));
#endif

    std::cout << "interpretation is finished" << std::endl;

    return parser.createExecutionSequenceDescription();
}

} // namespace vp
