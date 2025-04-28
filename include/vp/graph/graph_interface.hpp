#ifndef VP_GRAPH_INTERFACE_HPP
#define VP_GRAPH_INTERFACE_HPP

#include <functional>
#include <map>
#include <set>

namespace vp {

template <typename T>
class IGraph {
public:
    virtual ~IGraph() = default;

    virtual void addNode(const T &item) = 0;
    virtual void addEdge(const T &from, const T &to) = 0;
    [[nodiscard]] virtual bool isAcyclic() const = 0;

    using ValueType = std::reference_wrapper<T>;
    using EdgeMap = std::map<ValueType, std::set<ValueType>>;
};

} // namespace vp

#endif // VP_GRAPH_INTERFACE_HPP
