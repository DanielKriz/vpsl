#include <vp/dependency_graph.hpp>

namespace vp {
bool DependencyGraph::isAcyclic() const {
    if (m_isAcyclicityValid) {
        return m_isAcyclic;
    }

    DependencyGraph::ValueSet visited;
    DependencyGraph::ValueSet recursionStack;

    for (const auto &node : m_nodes) {
        if (not visited.contains(node)) {
            if (descent(node, visited, recursionStack)) {
                m_isAcyclic = false;
                return m_isAcyclic;
            }
        }
    }

    m_isAcyclic = true;
    return m_isAcyclic;
}

bool DependencyGraph::descent(
    const std::string_view &key,
    std::unordered_set<std::string_view> &visited,
    std::unordered_set<std::string_view> &recursionStack
) const {
    if (visited.contains(key)) {
        return false;
    }
    visited.insert(key);
    recursionStack.insert(key);

    for (const auto &neighbor : m_edges.at(key)) {
        if (not visited.contains(neighbor) and descent(neighbor, visited, recursionStack)) {
            return true;
        } 
        if (recursionStack.contains(neighbor)) {
            return true;
        }
    }
    recursionStack.erase(key);
    return false;
}

void DependencyGraph::topologySortHelper(
    const std::string_view &node,
    std::unordered_set<std::string_view> &visited,
    std::vector<std::string> &sorted
) const {
    visited.insert(node);

    if (not m_edges.contains(node)) {
        return;
    }

    for (const auto &neighbor : m_edges.at(node)) {
        if (not visited.contains(neighbor)) {
            topologySortHelper(neighbor, visited, sorted);
        }
    }
    sorted.emplace_back(node);
}

std::vector<std::string> DependencyGraph::topologySort() const noexcept {
    if (not isAcyclic()) {
        return {};
    }

    std::unordered_set<std::string_view> visited;
    std::vector<std::string> sorted;

    for (const auto& node : m_nodes) {
        if (not visited.contains(node)) {
            topologySortHelper(node, visited, sorted);
        }
    }
    return sorted;
}


} // namespace vp
