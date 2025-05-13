#include <vp/description/shader_code_store.hpp>

namespace vp::desc {

ShaderCode *ShaderCodeStore::emplace(const std::string &nameOfShader) {
    if (auto shaderCode = m_shaderCodes.find(nameOfShader); shaderCode != m_shaderCodes.end()) {
        return &shaderCode->second;
    }
    auto retval = m_shaderCodes.insert({nameOfShader, ShaderCode{nameOfShader}});
    return &retval.first->second;
}

ShaderCode *ShaderCodeStore::emplaceUnnamed() {
    return &m_unnamedShaderCodes.emplace_back();
}

bool ShaderCodeStore::contains(const std::string &nameOfShader) const noexcept {
    return m_shaderCodes.contains(nameOfShader);
}

void ShaderCodeStore::addDependencies(const std::string &nameOfShader, const std::vector<std::string> &others) {
    if (not contains(nameOfShader)) {
        throw std::runtime_error("It is not possible to add dependency to non-existent shader");
    }
    for (const std::string &otherShader : others) {
        m_dependecies.addEdge(nameOfShader, otherShader);
        if (not contains(otherShader)) {
            emplace(otherShader);
        }
    }
}

void ShaderCodeStore::insert(const std::string &nameOfShader, ShaderCode obj) {
    m_shaderCodes.insert({nameOfShader, std::move(obj)});
}

void ShaderCodeStore::insert(const std::string &nameOfShader, ShaderCode &&obj) {
    m_shaderCodes.insert({nameOfShader, std::move(obj)});
}

ShaderCode *ShaderCodeStore::getShaderCode(const std::string &nameOfShader) try {
    return &m_shaderCodes.at(nameOfShader);
} catch (std::exception &e) {
    throw std::runtime_error(fmt::format("Could not find shader '{}' in the store", nameOfShader));
}

const ShaderCode *ShaderCodeStore::getShaderCode(const std::string &nameOfShader) const try {
    return &m_shaderCodes.at(nameOfShader);
} catch (std::exception &e) {
    throw std::runtime_error(fmt::format("Could not find shader '{}' in the store", nameOfShader));
}

void ShaderCodeStore::clear() {
    m_shaderCodes.clear();
    m_unnamedShaderCodes.clear();
    m_dependecies.clear();
}

} // namespace vp::desc
