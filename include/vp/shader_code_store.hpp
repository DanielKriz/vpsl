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
    void insert(const std::string &nameOfShader, ShaderObject obj);
    void getCodeFor(const std::string &nameOfShader);

private:
std::unordered_map<std::string, ShaderObject> m_shaderCodes;
DependencyGraph m_dependecies;
}; 

} // namespace vp

#endif // VP_SHADER_CODE_STORE_HPP
