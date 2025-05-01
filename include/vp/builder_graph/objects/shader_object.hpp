#ifndef VP_BUILDER_GRAPH_SHADER_OBJECT_HPP
#define VP_BUILDER_GRAPH_SHADER_OBJECT_HPP

#include <algorithm>
#include <string>
#include <vector>

#include <fmt/core.h>

#include <vp/builder_graph/objects/builder_object_interface.hpp>

namespace vp {

class ShaderObject : public IBuilderGraphObject {
public:
    void addLine(std::string line) { m_lines.emplace_back(std::move(line)); }
    void addToPrependSet(ShaderObject &other);
    void addToAppendSet(ShaderObject &other);

    bool isInPrependSet(ShaderObject &other) const noexcept;
    bool isInAppendSet(ShaderObject &other) const noexcept;
    [[nodiscard]] bool isEmpty() const noexcept { return m_lines.empty() and m_prependSet.empty() and m_appendSet.empty(); }

    void appendLines(const std::vector<std::string> &lines);
    void appendLines(const ShaderObject &other);

    void prependLines(const std::vector<std::string> &lines);
    void prependLines(const ShaderObject &other);

    const std::vector<std::string> &getLines() const noexcept { return m_lines; }

    void compose();
    [[nodiscard]] std::string createSource() const;
private:
    std::vector<std::string> m_lines;
    std::vector<std::reference_wrapper<ShaderObject>> m_prependSet;
    std::vector<std::reference_wrapper<ShaderObject>> m_appendSet;
};

} // namespace vp

#endif // VP_BUILDER_GRAPH_SHADER_OBJECT_HPP
