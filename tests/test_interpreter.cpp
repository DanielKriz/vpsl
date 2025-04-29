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

TEST_CASE("First true test") {
    const std::string src = R"(
#pragma vp shader \
type(vertex)
)";
    auto interpreter = Interpreter(src);
    CHECK_NOTHROW(interpreter.interpret());
}

TEST_CASE("simple scope") {
    const std::string src = R"(
#pragma vp begin
#pragma vp end
)";
    auto interpreter = Interpreter(src);
    CHECK_NOTHROW(interpreter.interpret());
}

TEST_CASE("simple out of scope") {
    const std::string src = R"(
#pragma vp end
)";
    auto interpreter = Interpreter(src);
    CHECK_THROWS(interpreter.interpret());
}

TEST_SUITE_END();
