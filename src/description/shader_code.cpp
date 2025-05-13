#include <vp/description/shader_code.hpp>

namespace vp {

void ShaderCode::addToPrependSet(ShaderCode &other) {
    if (not isInPrependSet(other)) {
        m_prependSet.emplace_back(other);
    }
}

void ShaderCode::addToAppendSet(ShaderCode &other) {
    if (not isInAppendSet(other)) {
        m_appendSet.emplace_back(other);
    }
}

bool ShaderCode::isEmpty() const noexcept {
    return m_lines.empty() and m_prependSet.empty() and m_appendSet.empty(); 
}

bool ShaderCode::isComposed() const noexcept {
    return m_isComplete;
}

bool ShaderCode::isInPrependSet(ShaderCode &other) const noexcept {
    auto item = std::ranges::find_if(
        m_prependSet,
        [&other](const std::reference_wrapper<ShaderCode> &ref) {
            return std::addressof(ref.get()) == std::addressof(other);
        });
    return item != m_prependSet.end();
}

bool ShaderCode::isInAppendSet(ShaderCode &other) const noexcept {
    auto item = std::ranges::find_if(
        m_appendSet,
        [&other](const std::reference_wrapper<ShaderCode> &ref) {
            return std::addressof(ref.get()) == std::addressof(other);
        });
    return item != m_appendSet.end();
}

void ShaderCode::appendLines(const ShaderCode &other) {
    appendLines(other.getLines());
}

void ShaderCode::appendLines(const std::vector<std::string> &lines) {
    m_lines.insert(m_lines.end(), lines.cbegin(), lines.cend());
}

void ShaderCode::prependLines(const ShaderCode &other) {
    prependLines(other.getLines());
}

void ShaderCode::prependLines(const std::vector<std::string> &lines) {
    m_lines.insert(m_lines.begin(), lines.cbegin(), lines.cend());
}

void ShaderCode::compose() {
    if (isComposed()) {
        return;
    }

    for (const auto &obj : m_prependSet) {
        if (not obj.get().isComposed()) {
            obj.get().compose();
        }
        prependLines(obj);
    }
    for (const auto &obj : m_appendSet) {
        if (not obj.get().isComposed()) {
            obj.get().compose();
        }
        appendLines(obj);
    }
    m_isComplete = true;
}

[[nodiscard]] std::string ShaderCode::createSource() const {
    std::string src;
    for (const auto& line : m_lines) {
        src += fmt::format("{}\n", line);
    }
    return src;
}

void ShaderCode::setKind(ShaderCodeKind kind) noexcept {
    m_kind = kind;
}

ShaderCodeKind ShaderCode::getKind() const noexcept {
    return m_kind;
}

std::ostream &operator<<(std::ostream &os, const ShaderCode &obj) {
    return os << obj.createSource();
}

} // namespace vp
