#include <doctest/doctest.h>
#include <vp/dependency_graph.hpp>

using namespace vp;

TEST_SUITE_BEGIN("Dependency Graph");

TEST_CASE("Acyclicity") {
    internal::DependencyGraph dp;
    dp.addNode("A");
    dp.addNode("B");
    dp.addNode("C");
    dp.addEdge("A", "B");
    dp.addEdge("B", "C");
    dp.addEdge("A", "C");

    CHECK(dp.isAcyclic());
}

TEST_SUITE_END;
