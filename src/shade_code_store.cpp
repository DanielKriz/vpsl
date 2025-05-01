#include <vp/shader_code_store.hpp>

namespace vp {

ShaderObject &ShaderCodeStore::emplace(const std::string &nameOfShader) {

}

ShaderObject &ShaderCodeStore::emplaceUnnamed() {

}

void ShaderCodeStore::addDependencies(const std::string &nameOfShader, const std::vector<std::string> &others) {

}

void ShaderCodeStore::insert(const std::string &nameOfShader, ShaderObject obj) {

}

const ShaderObject &ShaderCodeStore::getShaderObject(const std::string &nameOfShader) {

}

} // namespace vp
