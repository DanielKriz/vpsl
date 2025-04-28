#include <doctest/doctest.h>
#include <vp/dependency_graph.hpp>

using namespace vp;

TEST_SUITE_BEGIN("Dependency Graph");

TEST_CASE("insertion of a node") {
    DependencyGraph dp;
    dp.addNode("A");
    CHECK(dp.containsNode("A"));
}

TEST_CASE("Graph does not contain noes that were not inserted") {
    DependencyGraph dp;
    CHECK_FALSE(dp.containsNode("A"));
}

TEST_CASE("insertion of an edge") {
    DependencyGraph dp;
    dp.addNode("A");
    dp.addNode("B");
    dp.addEdge("A", "B");
    CHECK(dp.containsEdge("A", "B"));
}

TEST_CASE("insertion of an edge inserts nodes too") {
    DependencyGraph dp;
    dp.addEdge("A", "B");
    REQUIRE(dp.containsEdge("A", "B"));
    CHECK(dp.containsNode("A"));
    CHECK(dp.containsNode("B"));
}

TEST_CASE("Graph does not contain noes that were not inserted") {
    DependencyGraph dp;
    CHECK_FALSE(dp.containsEdge("A", "B"));
}

TEST_CASE("Graph without nodes is acyclic") {
    DependencyGraph dp;
    CHECK(dp.isAcyclic());
}

TEST_CASE("Graph without edges is acyclic") {
    DependencyGraph dp;
    dp.addNode("A");
    dp.addNode("B");
    CHECK(dp.isAcyclic());
}

TEST_CASE("Simplest Acyclic graph check") {
    DependencyGraph dp;
    dp.addNode("A");
    dp.addEdge("A", "A");
    CHECK_FALSE(dp.isAcyclic());
}

TEST_CASE("Graph that is acyclic should not be marked as cyclic") {
    DependencyGraph dp;
    dp.addNode("A");
    dp.addNode("B");
    dp.addNode("C");
    dp.addEdge("A", "B");
    dp.addEdge("B", "C");
    dp.addEdge("A", "C");

    CHECK(dp.isAcyclic());
}

TEST_SUITE_END;
