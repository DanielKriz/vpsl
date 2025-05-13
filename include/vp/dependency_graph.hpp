#ifndef VP_DEPENDENCY_GRAPH
#define VP_DEPENDENCY_GRAPH

#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <fmt/core.h>

namespace vp {
class DependencyGraph {
public:
    using ValueType = std::string;
    using ValueSet = std::unordered_set<ValueType>;
    using EdgeMap = std::unordered_map<ValueType, ValueSet>;

    void addNode(const ValueType &item);

    bool containsNode(const ValueType &item) const;

    bool containsEdge(const ValueType &from, const ValueType &to) const;

    void addEdge(const ValueType &from, const ValueType &to);

    bool isAcyclic() const;

    [[nodiscard]] std::vector<std::string> topologySort() const noexcept;

#if 1
    void debugPrint() {
        fmt::println("\nDependency Graph Debug Print:");
        for (const auto &edge : m_edges) {
            for (const auto &to : edge.second) {
                fmt::println("\t{} -> {}", edge.first, to);
            }
        }
        fmt::println("");
    }
#endif

private:
    bool descent(
        const ValueType &key,
        ValueSet &visited,
        ValueSet &recursionStack
    ) const;

    void topologySortHelper(
        const std::string&node,
        ValueSet &visited,
        std::vector<std::string> &sorted
    ) const;

    mutable bool m_isAcyclic;
    mutable bool m_isAcyclicityValid;
    ValueSet m_nodes;
    EdgeMap m_edges;
};

} // namespace vp

#endif // VP_DEPENDENCY_GRAPH
