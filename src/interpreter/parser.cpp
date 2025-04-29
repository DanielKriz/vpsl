#include <vp/interpreter/parser.hpp>

namespace vp {

void Parser::setCurrentNode(vp::build::INode &pOther) {
}

vp::build::INode &Parser::getCurrentNode() {
    return m_CurrentNode;
}

bool Parser::isCurrentNodeRoot() const {
    return {};
}

void Parser::pushScope(ParserStage stage) {
}

void Parser::popScope() {
}

ParserStage Parser::peekScope() const {
    return {};
}

bool Parser::isScopeEmpty() const noexcept {
    return {};
}

}
