#include <vp/interpreter/shader_table.hpp>

namespace vp {

void ShaderTable::add(const std::string &name, ShaderBuilder &builder) {
    ShaderTable::getInstance().m_map.emplace(name, builder);
}

} // namespace vp
