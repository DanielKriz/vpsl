#include <fmt/base.h>
#include <vp/dependency_graph.hpp>

#include <iostream>
#include <ranges>
#include <queue>
#include <unordered_set>
#include <algorithm>

namespace vp::internal {

bool DependencyGraph::isAcyclic() const {

#warning "might be used"
#if 0
    std::queue<std::string> open;
    {
        std::set<std::string> hasIncomingEdge;
        for (auto &kvp : m_edges) {
            for (auto &node : kvp.second) {
                hasIncomingEdge.insert(node);
            }
        }
        std::vector<std::string> tmp;
        std::ranges::set_symmetric_difference(
            m_nodes,
            hasIncomingEdge,
            std::back_inserter(tmp)
        );
        std::ranges::for_each(tmp, [&open](auto &value) { open.push(value); });
    }
#endif

    // 1. compose the list of nodes with no incoming edges
    // 2. detect cycle with dfs for each of these nodes

    std::unordered_set<std::string> visited;

    std::function<bool (const std::string &)> descent = [&](const std::string &key) -> bool {
        visited.insert(key);

        std::cout << "Adding to visited: " << key << std::endl;

        bool isAcyclic = true;

        if (not m_edges.contains(key)) {
            return isAcyclic;
        }

        for (const auto &node : m_edges.at(key)) {
            if (visited.contains(node) or descent(node)) {
                std::cout << "Is something descending for: " << node << std::endl;
                isAcyclic = false;
                break;
            }
        }

        visited.erase(key);
        return isAcyclic;
    };
    
    return descent(*m_nodes.begin());
}

}
