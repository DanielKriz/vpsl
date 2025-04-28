#include <doctest/doctest.h>
#include <vp/interpreter/interpreter.hpp>

using namespace vp;

TEST_SUITE_BEGIN("Interpreter");

TEST_CASE("It is possible to construct an interpreter with raw source") {
    std::string src = "empty source";
    auto interpreter = Interpreter(src);
}

TEST_CASE("It is possible to construct an interpreter with file stream") {
    std::ifstream fin;
    auto interpreter = Interpreter(fin);
}

TEST_SUITE_END();
