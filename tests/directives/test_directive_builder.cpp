#include <doctest/doctest.h>

#include <vp/interpreter/directive.hpp>

using namespace vp;

TEST_SUITE("Directives") {

TEST_CASE("It is possible to instantiate a builder") {
    CHECK_NOTHROW(DirectiveBuilder{});
}

TEST_CASE("Building a directive with builder") {
    auto builder = DirectiveBuilder{};
    const Directive directive = builder.build();
    CHECK(std::is_same_v<decltype(directive), const Directive>);
}

TEST_CASE("It is not possible to copy unfinished directive") {
    auto builder = DirectiveBuilder();
    CHECK_THROWS(builder.copy());
}

}
