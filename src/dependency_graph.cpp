#include <vp/dependency_graph.hpp>

namespace vp {
bool DependencyGraph::isAcyclic() const {
    // Graph without nodes is implicitly acyclic
    if (m_nodes.empty()) {
        return true;
    }

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
    const std::string&key,
    std::unordered_set<std::string> &visited,
    std::unordered_set<std::string> &recursionStack
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
    const std::string&node,
    std::unordered_set<std::string> &visited,
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

    std::unordered_set<std::string> visited;
    std::vector<std::string> sorted;

    for (const auto& node : m_nodes) {
        if (not visited.contains(node)) {
            topologySortHelper(node, visited, sorted);
        }
    }
    return sorted;
}

void DependencyGraph::addNode(const ValueType &item) {
    m_nodes.insert(item);
    m_edges[item];
    m_isAcyclicityValid = false;
}

bool DependencyGraph::containsNode(const ValueType &item) const {
    return m_nodes.contains(item);
}

bool DependencyGraph::containsEdge(const ValueType &from, const ValueType &to) const {
    if (not containsNode(from)) {
        return false;
    }
    return m_edges.at(from).contains(to);
}

void DependencyGraph::addEdge(const ValueType &from, const ValueType &to) {
    m_nodes.insert(from);
    m_nodes.insert(to);
    m_edges[from].insert(to);
    m_edges[to];
    m_isAcyclicityValid = false;
}


} // namespace vp
