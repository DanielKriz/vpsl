#include <doctest/doctest.h>

TEST_SUITE_BEGIN("Parser");

TEST_CASE("smoke test") {
    REQUIRE(true == true);
}

TEST_CASE("second smoke test") {
    REQUIRE(false == false);
}

TEST_SUITE_END();
