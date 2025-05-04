#include <vp/shader_code_store.hpp>

namespace vp {

ShaderObject *ShaderCodeStore::emplace(const std::string &nameOfShader) {
    auto retval = m_shaderCodes.insert({nameOfShader, {}});
    return &retval.first->second;
}

ShaderObject *ShaderCodeStore::emplaceUnnamed() {
    return &m_unnamedShaderCodes.emplace_back();
}

bool ShaderCodeStore::contains(const std::string &nameOfShader) const noexcept {
    return {};
}

void ShaderCodeStore::addDependencies(const std::string &nameOfShader, const std::vector<std::string> &others) {

}

void ShaderCodeStore::insert(const std::string &nameOfShader, ShaderObject obj) {
    m_shaderCodes.insert({nameOfShader, std::move(obj)});
}

void ShaderCodeStore::insert(const std::string &nameOfShader, ShaderObject &&obj) {
    m_shaderCodes.insert({nameOfShader, std::move(obj)});
}

ShaderObject *ShaderCodeStore::getShaderObject(const std::string &nameOfShader) {
    return &m_shaderCodes.at(nameOfShader);
}

const ShaderObject *ShaderCodeStore::getShaderObject(const std::string &nameOfShader) const {
    return &m_shaderCodes.at(nameOfShader);
}

} // namespace vp
