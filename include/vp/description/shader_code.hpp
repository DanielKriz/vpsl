#ifndef VP_DESCRIPTION_SHADER_CODE_HPP
#define VP_DESCRIPTION_SHADER_CODE_HPP

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <fmt/core.h>

#include <vp/types.hpp>
#include <vp/utils.hpp>

namespace vp {

enum class ShaderCodeKind : enum32 {
    Unkown,
    Generic,
    Fragment,
    Vertex,
    TesselationControl,
    TesselationEvaluation,
    Geometry,
    Compute,
};

inline std::ostream &operator<<(std::ostream &os, const ShaderCodeKind kind) {
    std::string_view shaderRepr = [&kind]() {
        using enum ShaderCodeKind;
        switch (kind) {
        case Unkown: return "Unknown";
        case Generic: return "Generic";
        case Fragment: return "Fragment";
        case Vertex: return "Vertex";
        case TesselationControl: return "Tessellation Control";
        case TesselationEvaluation: return "Tessellation Evaluation";
        case Geometry: return "Geometry";
        case Compute: return "Compute";
        }
        return "";
    }();
    return os << shaderRepr;
}

template <>
inline std::unordered_map<std::string_view, ShaderCodeKind> utils::StringToEnumMap<ShaderCodeKind>::map = {
    { "generic", ShaderCodeKind::Generic },
    { "vertex", ShaderCodeKind::Vertex },
    { "fragment", ShaderCodeKind::Fragment },
    { "geometry", ShaderCodeKind::Geometry },
    { "compute", ShaderCodeKind::Compute },
    { "tesselation_control", ShaderCodeKind::TesselationControl },
    { "tesselation_evaluation", ShaderCodeKind::TesselationEvaluation },
};

class ShaderCode final {
public:
    ShaderCode() = default;
    explicit ShaderCode(std::string name) : m_name(std::move(name)) {};

    void addLine(std::string line) { m_lines.emplace_back(std::move(line)); }
    void addToPrependSet(ShaderCode &other);
    void addToAppendSet(ShaderCode &other);

    bool isInPrependSet(ShaderCode &other) const noexcept;
    bool isInAppendSet(ShaderCode &other) const noexcept;
    [[nodiscard]] bool isEmpty() const noexcept;

    void appendLines(const std::vector<std::string> &lines);
    void appendLines(const ShaderCode &other);

    void prependLines(const std::vector<std::string> &lines);
    void prependLines(const ShaderCode &other);

    [[nodiscard]] const std::vector<std::string> &getLines() const noexcept { return m_lines; }

    [[nodiscard]] bool isComposed() const noexcept;
    void compose();
    [[nodiscard]] std::string createSource() const;

    friend std::ostream &operator<<(std::ostream &os, const ShaderCode &obj);

    void setKind(ShaderCodeKind kind) noexcept;
    [[nodiscard]] ShaderCodeKind getKind() const noexcept;

    [[nodiscard]] bool isNamed() const noexcept { return !m_name.empty(); }
    [[nodiscard]] const std::string &getName() const noexcept { return m_name; }
private:
    ShaderCodeKind m_kind { ShaderCodeKind::Unkown };
    std::vector<std::string> m_lines;
    std::vector<std::reference_wrapper<ShaderCode>> m_prependSet;
    std::vector<std::reference_wrapper<ShaderCode>> m_appendSet;
    std::string m_name;
    bool m_isComplete { false };
};

} // namespace vp

#endif // VP_DESCRIPTION_SHADER_CODE_HPP
