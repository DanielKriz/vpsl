#ifndef VP_DESCRIPTION_SHADER_CODE_STORE_HPP
#define VP_DESCRIPTION_SHADER_CODE_STORE_HPP

#include <vp/dependency_graph.hpp>
#include <vp/description/shader_code.hpp>
#include <vp/singleton.hpp>

#include <fmt/core.h>

namespace vp::desc {

/// @brief Storage of code for all shaders
///
/// Storage of code for all shaders, however it also manages dependencies
/// between them, because they are kept as lazy values, unless needed.
class ShaderCodeStore : public Singleton<ShaderCodeStore> {
public:
    friend Singleton<ShaderCodeStore>;

    ShaderCodeStore(const ShaderCodeStore &other) = delete;
    ShaderCodeStore(ShaderCodeStore &&other) noexcept = delete;
    ShaderCodeStore& operator=(const ShaderCodeStore &other) = delete;
    ShaderCodeStore& operator=(ShaderCodeStore &&other) = delete;
    ~ShaderCodeStore() = default;

    ShaderCode *emplace(const std::string &nameOfShader);
    ShaderCode *emplaceUnnamed();

    [[nodiscard]] bool areDependenciesValid() const noexcept;
    void addDependencies(const std::string &nameOfShader, const std::vector<std::string> &others);

    void insert(const std::string &nameOfShader, ShaderCode obj);
    void insert(const std::string &nameOfShader, ShaderCode &&obj);

    bool contains(const std::string &nameOfShader) const noexcept;

    ShaderCode *getShaderCode(const std::string &nameOfShader);
    const ShaderCode *getShaderCode(const std::string &nameOfShader) const;
    ShaderCode *operator[](const std::string &nameOfShader) {
        return getShaderCode(nameOfShader);
    }
    const ShaderCode *operator[](const std::string &nameOfShader) const {
        return getShaderCode(nameOfShader);
    };

    void composeAllShaders();

    void clear();

    friend std::ostream &operator<<(std::ostream &os, const ShaderCodeStore &store);
private:
std::unordered_map<std::string, ShaderCode> m_shaderCodes;
std::vector<ShaderCode> m_unnamedShaderCodes;
DependencyGraph m_dependecies;
    ShaderCodeStore() = default;
}; 

} // namespace vp::desc

#endif // VP_DESCRIPTION_SHADER_CODE_STORE_HPP
