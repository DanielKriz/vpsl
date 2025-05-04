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

class Parser {
public:
    Parser() : m_CurrentNode(m_graph.getRoot()) {}
    ~Parser() = default;

    void setCurrentNode(vp::build::INode &pOther);
    vp::build::INode &getCurrentNode();
    bool isCurrentNodeRoot() const;

    void pushScope(ParserStage stage);
    void popScope();
    ParserStage peekScope() const;
    bool isScopeEmpty() const noexcept;

    Parser(const Parser &other) = delete;
    Parser &operator=(const Parser &other) = delete;
    Parser(Parser &&other) = delete;
    Parser &operator=(Parser &&other) = delete;

    // TODO: make this optional
    static std::unique_ptr<IDirective> constructDirectiveFromToken(const Token &token) {
        TokenKind kind = token.getTokenKind();
        switch (kind) {
        case TokenKind::ShaderDirective:
            return std::make_unique<ShaderDirective>();
        case TokenKind::ProgramDirective:
            return std::make_unique<ProgramDirective>();
        case TokenKind::LoadDirective:
            return std::make_unique<LoadDirective>();
        case TokenKind::BeginDirective:
            return std::make_unique<BeginDirective>();
        case TokenKind::EndDirective:
            return std::make_unique<EndDirective>();
        case TokenKind::TextureDirective:
        default:
            return nullptr;
        }
    }

private:
    vp::DependencyGraph m_shaderDependencyGraph;
    vp::DependencyGraph m_programDependencyGraph;

    vp::build::BuilderGraph m_graph;
    vp::build::INode &m_CurrentNode;

    std::stack<ParserStage> m_scope;
};

} // namespace vp

#endif // VP_INTERPRETER_PARSER_HPP
