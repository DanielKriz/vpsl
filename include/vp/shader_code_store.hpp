#ifndef VP_SHADER_CODE_STORE_HPP
#define VP_SHADER_CODE_STORE_HPP

#include <vp/builder_graph/objects/shader_object.hpp>
#include <vp/dependency_graph.hpp>

namespace vp {

/// @brief Storage of code for all shaders
///
/// Storage of code for all shaders, however it also manages dependencies
/// between them, because they are kept as lazy values, unless needed.
class ShaderCodeStore {
public:
    ShaderObject *emplace(const std::string &nameOfShader);
    ShaderObject *emplaceUnnamed();

    void addDependencies(const std::string &nameOfShader, const std::vector<std::string> &others);
    void insert(const std::string &nameOfShader, ShaderObject obj);
    void insert(const std::string &nameOfShader, ShaderObject &&obj);

    bool contains(const std::string &nameOfShader) const noexcept;

    ShaderObject *getShaderObject(const std::string &nameOfShader);
    const ShaderObject *getShaderObject(const std::string &nameOfShader) const;
    ShaderObject *operator[](const std::string &nameOfShader) {
        return getShaderObject(nameOfShader);
    }
    const ShaderObject *operator[](const std::string &nameOfShader) const {
        return getShaderObject(nameOfShader);
    };

    void composeAllShaders();

private:
std::unordered_map<std::string, ShaderObject> m_shaderCodes;
std::vector<ShaderObject> m_unnamedShaderCodes;
DependencyGraph m_dependecies;
}; 

} // namespace vp

#endif // VP_SHADER_CODE_STORE_HPP
