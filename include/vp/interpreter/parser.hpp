#ifndef VP_INTERPRETER_PARSER_HPP
#define VP_INTERPRETER_PARSER_HPP

#include <vp/dependency_graph.hpp>
#include <vp/description/program_description.hpp>
#include <vp/description/shader_code_store.hpp>
#include <vp/interpreter/directive.hpp>
#include <vp/interpreter/token.hpp>

namespace vp {

class ShaderObject;
class ProgramObject;

enum class ParserScope : u8 {
    Global,
    GlobalShader,
    Program,
    Shader
};

class Parser final {
public:
    Parser() : m_store(desc::ShaderCodeStore::getInstance()) {};
    ~Parser() = default;

    void pushScope();
    void pushGlobalShaderScope();
    void popScope();
    ParserScope peekScope() const;

    Parser(const Parser &other) = delete;
    Parser &operator=(const Parser &other) = delete;
    Parser(Parser &&other) = delete;
    Parser &operator=(Parser &&other) = delete;

    static std::optional<Directive> createDirectiveFromToken(const Token &token);

    ShaderCode *shaderCodeFromDirective(Directive &dir, desc::ProgramDescriptionBuilder &builder);

    Options &getGlobalOptions() noexcept { return m_globalOptions; }

    std::vector<desc::ProgramDescription> createExecutionSequenceDescription();

    void addProgramDescription(desc::ProgramDescription &desc);
    void addProgramDescription(desc::ProgramDescription &&desc);

    void applyOptionDirective(Directive &dir, Options &localOpts);

private:
    static bool isOptionPersistent(Directive &dir);
    void handleValueOption(Directive &dir, Options &localOpts);
    void handleEnableOption(Directive &dir, Options &localOpts);

    vp::DependencyGraph m_programDependencyGraph;

    Options m_globalOptions;
    desc::ShaderCodeStore &m_store;
    std::vector<desc::ProgramDescription> m_programDescriptions;
    ParserScope m_stage { ParserScope::Global };
};

} // namespace vp

#endif // VP_INTERPRETER_PARSER_HPP
