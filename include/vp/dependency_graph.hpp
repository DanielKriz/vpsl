#ifndef VP_DEPENDENCY_GRAPH
#define VP_DEPENDENCY_GRAPH

#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace vp {
class DependencyGraph {
public:
    using ValueType = std::string_view;
    using ValueSet = std::unordered_set<ValueType>;
    using EdgeMap = std::unordered_map<ValueType, ValueSet>;

    void addNode(const ValueType &item) {
        m_nodes.insert(item);
        m_edges[item];
        m_isAcyclicityValid = false;
    }

    bool containsNode(const ValueType &item) const {
        return m_nodes.contains(item);
    }

    bool containsEdge(const ValueType &from, const ValueType &to) const {
        if (not containsNode(from)) {
            return false;
        }
        return m_edges.at(from).contains(to);
    }

    void addEdge(const ValueType &from, const ValueType &to) {
        m_nodes.insert(from);
        m_nodes.insert(to);
        m_edges[from].insert(to);
        m_isAcyclicityValid = false;
    }

    bool isAcyclic() const;

    [[nodiscard]] std::vector<std::string> topologySort() const noexcept;

private:
    bool descent(
        const std::string_view &key,
        std::unordered_set<std::string_view> &visited,
        std::unordered_set<std::string_view> &recursionStack
    ) const;

    void topologySortHelper(
        const std::string_view &node,
        std::unordered_set<std::string_view> &visited,
        std::vector<std::string> &sorted
    ) const;

    mutable bool m_isAcyclic;
    mutable bool m_isAcyclicityValid;
    std::unordered_set<std::string_view> m_nodes;
    EdgeMap m_edges;
};

} // namespace vp

#endif // VP_DEPENDENCY_GRAPH
