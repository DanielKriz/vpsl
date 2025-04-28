#ifndef VP_GRAPH_HPP
#define VP_GRAPH_HPP

#include <vp/graph/graph_interface.hpp>

#include <set>

namespace vp {

template <typename T>
class Graph : public IGraph<T> {
public:
    virtual ~Graph() = default;

    void addNode(const T &item) override {}
    void addEdge(const T &from, const T &to) override {};
    [[nodiscard]] bool isAcyclic() const override {};

private:
    // It has to be mutable, because it is not direcly related to the data that the graph is
    // holding, it is just a simple optimization.
    mutable bool m_isAcyclic;
    mutable bool m_isAcyclicityValid;
    std::set<typename IGraph<T>::ValueType> m_nodes;
    IGraph<T>::EdgeMap m_edges;
};

} // namespace vp

#endif // VP_GRAPH_HPP
