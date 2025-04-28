#ifndef VP_DEPENDENCY_GRAPH
#define VP_DEPENDENCY_GRAPH

#include <functional>
#include <set>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace vp {

namespace internal {
    class DependencyGraph {
        public:
            void addNode(const std::string &item) { m_nodes.insert(item); }
            void addEdge(const std::string &from, const std::string &to) {
                if (not m_edges.contains(from)) {
                    m_edges.insert({from, {}});
                }
                m_edges.find(from)->second.insert(to);
            }
            bool isAcyclic() const;

            using ValueType = std::string;
            using EdgeMap = std::map<ValueType, std::set<ValueType>>;
        private:
            void depthFirstSearchDescent(const std::string &key, std::unordered_set<std::string> &visited) {

            }


            mutable bool m_isAcyclic;
            mutable bool m_isAcyclicityValid;
            std::set<ValueType> m_nodes;
            EdgeMap m_edges;
    };
}

// TODO: change the internal representation whether T has hash function implemented, because if it
// does, then it is possible to use unordered_* variants of data-structures

template <typename T>
class DependencyGraph {
public:
    void addNode(const T &item) {}
    void addEdge(const T &from, const T &to) {}
    bool isAcyclic() const { return {}; }

    using ValueType = std::reference_wrapper<T>;
    using EdgeMap = std::map<ValueType, std::set<ValueType>>;
private:
    mutable bool m_isAcyclic;
    mutable bool m_isAcyclicityValid;
    std::set<ValueType> m_nodes;
    EdgeMap m_edges;
};

} // namespace vp

#endif // VP_DEPENDENCY_GRAPH
