#include <vp/interpreter/interpreter.hpp>
#include <spdlog/spdlog.h>

#include <filesystem>

namespace vp {

Interpreter::Interpreter(const std::string &src)
    : m_stringStream(src)
    , m_inputStream(m_stringStream.rdbuf()) 
    , m_pInputStream(std::make_unique<std::istream>(m_stringStream.rdbuf()))
    {
    // So that the application is in defined state
    desc::ShaderCodeStore::getInstance().clear();
}

Interpreter::Interpreter(std::ifstream &fin)
    : m_inputStream(fin.rdbuf())
    , m_pInputStream(std::make_unique<std::istream>(fin.rdbuf()))
{
    // So that the application is in defined state
    desc::ShaderCodeStore::getInstance().clear();
    resolveIncludes();
}

void Interpreter::resolveIncludes() {
    Lexer lexer{};
    std::string line{};
    std::streampos oldPos = m_inputStream.tellg();

    while (m_inputStream.peek() != EOF) {
        oldPos = m_inputStream.tellg();
        std::getline(m_inputStream, line);
        if (Lexer::isContinuous(line)) {
            std::string tmp;
            std::getline(m_inputStream, tmp);
            Lexer::joinLines(line, tmp);
        }

        std::optional<std::vector<Token>> tokens = lexer.scan(line);

        if (not tokens.has_value() or tokens->empty()) {
            break;
        }

        const auto directiveToken = *tokens->cbegin();
        tokens->erase(tokens->begin());
        const auto &clauseTokens = *tokens;

        auto directive = Parser::createDirectiveFromToken(directiveToken);
        if (directive->getDirectiveKind() != DirectiveKind::Include) {
            break;
        }

        directive->areClausesCorrect(clauseTokens);

        directive->populateClauses(clauseTokens);
        auto pathValue = directive->getParameter<ClauseKind::Path>();
        if (not pathValue.has_value()) {
            throw std::runtime_error("Missing path for include directive");
        }
        const auto path = std::filesystem::path{ *pathValue };

        std::ifstream fin { path };
        if (not fin.is_open()) {
            throw std::runtime_error(fmt::format("Could not open the file '{}'", path.string()));
        }
        m_stringStream << fin.rdbuf();
    }
    m_inputStream.seekg(oldPos);
    m_stringStream << m_inputStream.rdbuf();
    m_pInputStream = std::make_unique<std::istream>(m_stringStream.rdbuf());
}

std::vector<desc::ProgramDescription> Interpreter::interpret() {
    Lexer lexer{};
    Parser parser{};

    std::string line{};

    desc::ShaderCodeStore &store = desc::ShaderCodeStore::getInstance();

    ShaderCode globalShaderCode = ShaderCode{};
    ShaderCode *pCurrentShaderCode = &globalShaderCode;
    desc::ProgramDescriptionBuilder programBuilder;
    Options localOptions = parser.getGlobalOptions();

    bool isLastDirectiveShader = false;

    while (std::getline(*m_pInputStream, line)) {
        if (Lexer::isContinuous(line)) {
            std::string tmp;
            std::getline(*m_pInputStream, tmp);
            Lexer::joinLines(line, tmp);
        }

        std::optional<std::vector<Token>> tokens = lexer.scan(line);
        // Skip empty lines
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
            throw std::runtime_error(
                fmt::format("No directive was created from '{}'", directiveToken)
            );
        }

        directive->populateClauses(clauseTokens);

        DirectiveKind directiveKind = directive->getDirectiveKind();
        if (directiveKind == DirectiveKind::Shader) {
            pCurrentShaderCode = parser.shaderCodeFromDirective(*directive, programBuilder);
            pCurrentShaderCode->appendLines(globalShaderCode);

        } else if (directiveKind == DirectiveKind::Program) {
            auto name = directive->getParameter<ClauseKind::Name>();
            if (name.has_value()) {
                programBuilder.setName(*name);
            } else {
                programBuilder.setNameFromID();
            }

        } else if (directiveKind == DirectiveKind::Load) {
            if (parser.peekScope() != ParserScope::Global) {
                throw std::runtime_error("Cannot use load directive outside of global scope");
            }

        } else if (directiveKind == DirectiveKind::Include) {
            throw std::runtime_error("Include directive can exist only at the beggingin of the file");

        } else if (directiveKind == DirectiveKind::FrameBuffer) {
            if (parser.peekScope() == ParserScope::Shader) {
                throw std::runtime_error("Cannot use frambuffer directive inside of shader scope");
            }

        } else if (directiveKind == DirectiveKind::ResourceStore) {
            if (parser.peekScope() != ParserScope::Global) {
                throw std::runtime_error("Cannot use resource_store directive outside of global scope");
            }

        } else if (directiveKind == DirectiveKind::CopyIn) {
            if (parser.peekScope() != ParserScope::Shader) {
                throw std::runtime_error("Cannot use copyin directive outside of shader scope");
            }

        } else if (directiveKind == DirectiveKind::Option) {
            if (parser.peekScope() == ParserScope::Shader) {
                throw std::runtime_error("Cannot use option directive inside of shader scope");
            }
            parser.applyOptionDirective(*directive, localOptions);

        } else if (directiveKind == DirectiveKind::Begin) {
            if (isLastDirectiveShader and parser.peekScope() == ParserScope::Global) {
                parser.pushGlobalShaderScope();
            } else {
                parser.pushScope();
            }

        } else if (directiveKind == DirectiveKind::End) {
            if (parser.peekScope() == ParserScope::Program) {
                programBuilder.setOptions(localOptions);
                parser.addProgramDescription(programBuilder.build());
                localOptions = parser.getGlobalOptions();
                programBuilder.reset();
            }
            parser.popScope();

        } else {
            throw std::runtime_error("Unknown Directive kind!");
        }

        isLastDirectiveShader = directiveKind == DirectiveKind::Shader;
#if 0
        fmt::println("finished iteration");
#endif
    }

    store.composeAllShaders();

    spdlog::debug("Interpretation finished");
    return parser.createExecutionSequenceDescription();
}

} // namespace vp
