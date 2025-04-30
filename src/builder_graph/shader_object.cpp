#include <vp/builder_graph/objects/shader_object.hpp>

namespace vp {

void ShaderObject::addToPrependSet(ShaderObject &other) {
    if (not isInPrependSet(other)) {
        m_prependSet.emplace_back(other);
    }
}

void ShaderObject::addToAppendSet(ShaderObject &other) {
    if (not isInAppendSet(other)) {
        m_appendSet.emplace_back(other);
    }
}

bool ShaderObject::isInPrependSet(ShaderObject &other) const noexcept {
    auto item = std::find_if(
        m_prependSet.cbegin(),
        m_prependSet.cend(),
        [&other](const std::reference_wrapper<ShaderObject> &ref) {
            return std::addressof(ref.get()) == std::addressof(other);
        });
    return item != m_prependSet.end();
}

bool ShaderObject::isInAppendSet(ShaderObject &other) const noexcept {
    auto item = std::find_if(
        m_appendSet.cbegin(),
        m_appendSet.cend(),
        [&other](const std::reference_wrapper<ShaderObject> &ref) {
            return std::addressof(ref.get()) == std::addressof(other);
        });
    return item != m_appendSet.end();
}

void ShaderObject::appendLines(const ShaderObject &other) {
    appendLines(other.getLines());
}

void ShaderObject::appendLines(const std::vector<std::string> &lines) {

    m_lines.insert(m_lines.end(), lines.cbegin(), lines.cend());
}

void ShaderObject::prependLines(const ShaderObject &other) {
    prependLines(other.getLines());
}

void ShaderObject::prependLines(const std::vector<std::string> &lines) {
    m_lines.insert(m_lines.begin(), lines.cbegin(), lines.cend());
}

void ShaderObject::compose() {
    for (const auto &obj : m_prependSet) {
        prependLines(obj);
    }
    for (const auto &obj : m_appendSet) {
        appendLines(obj);
    }
}

[[nodiscard]] std::string ShaderObject::createSource() const {
    std::string src;
    for (const auto& line : m_lines) {
        src += fmt::format("{}\n", line);
    }
    return src;
}

} // namespace vp
