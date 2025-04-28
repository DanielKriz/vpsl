#ifndef VP_INTERPRETER_SHADER_TABLE_HPP
#define VP_INTERPRETER_SHADER_TABLE_HPP

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <memory>

#include <vp/singleton.hpp>
#include <vp/builder_graph/shader_builder.hpp>

namespace vp {

class ShaderBuilder;

class ShaderTable : public Singleton<ShaderTable> {
public:
    using Entry = std::optional<std::reference_wrapper<ShaderBuilder>>;

    static void add(const std::string &name, ShaderBuilder &builder);
    static bool contains(const std::string &name);
    static Entry &find(const std::string &name);

private:
    std::unordered_map<std::string, Entry> m_map;
};

} // namespace vp

#endif // VP_INTERPRETER_SHADER_TABLE_HPP
