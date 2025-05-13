#include <doctest/doctest.h>
#include <vp/interpreter/interpreter.hpp>

using namespace vp;

TEST_SUITE("Interpreter") {

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
    //CHECK_NOTHROW(interpreter.interpret());
}

TEST_CASE("Interpret can detect cycle in shader dependencies") {
    const std::string src = R"(
#pragma vp program name(main)
#pragma vp begin

#pragma vp shader name(main_vs) type(vertex) prepend(main:main_fs)
#pragma vp begin
// empty
#pragma vp end // main_vs
#pragma vp shader name(main_fs) type(fragment) append(main:main_vs)
#pragma vp begin
// empty
#pragma vp end // main_fs
#pragma vp end // main
)";
    auto interpreter = Interpreter(src);
    CHECK_THROWS(interpreter.interpret());
}

TEST_CASE("simple out of scope") {
    const std::string src = R"(
#pragma vp end
)";
    auto interpreter = Interpreter(src);
    CHECK_THROWS(interpreter.interpret());
}

TEST_CASE("load is not possible to use outside global scope") {
    const std::string src = R"(
#pragma vp program
#pragma vp begin
#pragma vp load
#pragma vp end
    )";
    auto interpreter = Interpreter(src);
    CHECK_THROWS(interpreter.interpret());
}

TEST_CASE("resource_store is not possible to use outside global scope") {
    const std::string src = R"(
#pragma vp program
#pragma vp begin
#pragma vp resource_store
#pragma vp end
    )";
    auto interpreter = Interpreter(src);
    CHECK_THROWS(interpreter.interpret());
}

TEST_CASE("include is not possible to use outside global scope") {
    const std::string src = R"(
#pragma vp program
#pragma vp begin
#pragma vp include
#pragma vp end
    )";
    auto interpreter = Interpreter(src);
    CHECK_THROWS(interpreter.interpret());
}

TEST_CASE("Simple working load program") {
    const std::string src = R"(
#pragma vp load
    )";
    auto interpreter = Interpreter(src);
    CHECK_NOTHROW(interpreter.interpret());
}

TEST_CASE("Simple working resource_store program") {
    const std::string src = R"(
#pragma vp resource_store
    )";
    auto interpreter = Interpreter(src);
    CHECK_NOTHROW(interpreter.interpret());
}

TEST_CASE("Simple working include program") {
    const std::string src = R"(
#pragma vp include
    )";
    auto interpreter = Interpreter(src);
    CHECK_NOTHROW(interpreter.interpret());
}

}
