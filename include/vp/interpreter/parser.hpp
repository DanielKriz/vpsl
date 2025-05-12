#ifndef VP_INTERPRETER_PARSER_HPP
#define VP_INTERPRETER_PARSER_HPP

#include <stack>
#include <memory>

#include <vp/builder_graph/graph.hpp>
#include <vp/dependency_graph.hpp>
#include <vp/interpreter/parser_stages.hpp>
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
    Parser() : m_CurrentNode(m_graph.getRoot()) {}
    ~Parser() = default;

    void pushScope();
    void pushGlobalShaderScope();
    void pushScope(ParserScope stage);
    void popScope();
    ParserScope peekScope() const;
    bool isScopeEmpty() const noexcept;

    Parser(const Parser &other) = delete;
    Parser &operator=(const Parser &other) = delete;
    Parser(Parser &&other) = delete;
    Parser &operator=(Parser &&other) = delete;

    static std::optional<Directive> createDirectiveFromToken(const Token &token);

private:
    vp::DependencyGraph m_shaderDependencyGraph;
    vp::DependencyGraph m_programDependencyGraph;

    vp::build::BuilderGraph m_graph;
    vp::build::INode &m_CurrentNode;

    desc::ShaderCodeStore &m_store;
    std::vector<desc::ProgramDescription> m_programDescriptions;
    ParserScope m_stage { ParserScope::Global };
};

} // namespace vp

#endif // VP_INTERPRETER_PARSER_HPP
