#include <filesystem>

#include <vp/interpreter/interpreter.hpp>
#include <vp/resources/resource_kind.hpp>
#include <vp/resources/resource_loader.hpp>
#include <vp/resources/resource_store.hpp>

#include <spdlog/spdlog.h>

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

    MeshData *meshPtr;

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

            auto drawParam = directive->getParameters<ClauseKind::Draw>();
            auto meshParam = directive->getParameter<ClauseKind::Mesh>();

            if (not drawParam.has_value() and not meshParam.has_value()) {
                throw std::runtime_error(
                    "Each program has to have either draw or mesh clause defined"
                );
            }

            if (drawParam.has_value()) {
                const auto drawMode = utils::mapStringToEnumKind<DrawMode>((*drawParam)[0]);
                const auto count = std::stoi((*drawParam)[1]);
                if (not drawMode.has_value()) {
                    throw std::runtime_error(
                        fmt::format("Unknown draw mode: '{}'!", (*drawParam)[0])
                    );
                }
                programBuilder.setDrawCommand(*drawMode, static_cast<u64>(count));
            } else {
                const auto meshName = *meshParam;

                if (not ResourceStore::getInstance().containsMesh(meshName)) {
                    throw std::runtime_error("Provided mesh for program is never loaded!");
                }

                programBuilder.setMesh(ResourceStore::getInstance().getMesh(meshName));

                meshPtr = &ResourceStore::getInstance().getMesh(meshName);
            }

        } else if (directiveKind == DirectiveKind::Load) {
            if (parser.peekScope() != ParserScope::Global) {
                throw std::runtime_error("Cannot use load directive outside of global scope");
            }

            const auto name = *directive->getParameter<ClauseKind::Name>();
            const auto subcommand = directive->getSubCommand();
            const auto path = *directive->getParameter<ClauseKind::Path>();

            spdlog::debug("Encountered loading with: {}, {}, {}", name, subcommand, path);

            if (subcommand == TokenKind::Texture) {
                ResourceStore::getInstance().addTexture(name, path);
            } else if (subcommand == TokenKind::Material) {
                ResourceStore::getInstance().addMaterial(name, path);
            } else if (subcommand == TokenKind::Mesh) {
                ResourceStore::getInstance().addMesh(name, path);
            } else {
                throw std::runtime_error(
                    fmt::format("Unhandled load subcommand: '{}'", subcommand)
                );
            }

        } else if (directiveKind == DirectiveKind::Texture) {
            spdlog::debug("found texture, bruh");

            static auto textureUniformRe = utils::compileRegularExpression(
                R"(\s*layout\s*\(\a*binding\s*=\s*(\d+)\a*\))"
            );

            u32 location {};
            std::getline(*m_pInputStream, line);
            if (RE2::PartialMatch(line, *textureUniformRe, &location)) {
                spdlog::info("Got uniform with location {}", location);
                const auto name = *directive->getParameter<ClauseKind::Name>();
                auto type = directive->getParameter<ClauseKind::Type>();
                auto format = directive->getParameter<ClauseKind::Format>();
                desc::TextureDescription desc;
                desc.location = location;
                if (type.has_value()) {
                    desc.kind = *utils::mapStringToEnumKind<TextureKind>(*type);
                }
                if (format.has_value()) {
                    desc.format = *utils::mapStringToEnumKind<TextureFormat>(*format);
                }
                desc.pTexture = &ResourceStore::getInstance().getTexture(name);
                programBuilder.addTexture(desc);
            } else {
                throw std::runtime_error("Could not match location for texture uniform");
            }

            // line has to be then added to the correct shader
            if (parser.peekScope() == ParserScope::Global) {
                globalShaderCode.addLine(line);
            } else if (parser.peekScope() == ParserScope::Program) {
                throw std::runtime_error("There cannot be a lone statement in program scope");
            } else {
                pCurrentShaderCode->addLine(line);
            }

        } else if (directiveKind == DirectiveKind::Include) {
            // Do nothing

        } else if (directiveKind == DirectiveKind::FrameBuffer) {
            if (parser.peekScope() == ParserScope::Shader) {
                throw std::runtime_error("Cannot use frambuffer directive inside of shader scope");
            }

        } else if (directiveKind == DirectiveKind::ResourceStore) {
            if (parser.peekScope() != ParserScope::Global) {
                throw std::runtime_error("Cannot use resource_store directive outside of global scope");
            }

            const auto path = *directive->getParameter<ClauseKind::Path>();
            ResourceStore::getInstance().addSearchPath(path);

        } else if (directiveKind == DirectiveKind::CopyIn) {
            if (parser.peekScope() != ParserScope::Shader) {
                throw std::runtime_error("Cannot use copyin directive outside of shader scope");
            }

            if (pCurrentShaderCode->getKind() != ShaderCodeKind::Vertex) {
                throw std::runtime_error("CopyIn directive can be used only in Vertex shaders!");
            }

            const auto name = *directive->getParameter<ClauseKind::Name>();
            const auto value = *directive->getParameter<ClauseKind::Value>();

            spdlog::debug("Got copyin directive for {} with value {}", name, value);

            const auto attr = utils::mapStringToEnumKind<AttributeType>(value);

            if (not attr.has_value()) {
                throw std::runtime_error("Invalid value for copyin directive");
            }

            u32 location {};
            static auto attrLocationRe = utils::compileRegularExpression(
                R"(\s*layout\s*\(\a*location\s*=\s*(\d+))"
            );

            std::getline(*m_pInputStream, line);
            if (RE2::PartialMatch(line, *attrLocationRe, &location)) {
                spdlog::debug("Got attribute location: {}", location);
                programBuilder.addAttributeToMesh(*attr, location);
            } else {
                throw std::runtime_error(
                    "Location has to specified for attributes using the copyin directive"
                );
            }

            // line has to be then added to the correct shader
            if (parser.peekScope() == ParserScope::Global) {
                globalShaderCode.addLine(line);
            } else if (parser.peekScope() == ParserScope::Program) {
                throw std::runtime_error("There cannot be a lone statement in program scope");
            } else {
                pCurrentShaderCode->addLine(line);
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

    ResourceStore::getInstance().evaluateLazyResources();

    spdlog::debug("Interpretation finished");
    return parser.createExecutionSequenceDescription();
}

} // namespace vp
