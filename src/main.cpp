#include <fstream>
#include <set>

#include <fmt/core.h>

#include <vp/error_handling.hpp>
#include <vp/interpreter/interpreter.hpp>
#include <vp/interpreter/lexer.hpp>
#include <vp/interpreter/directive.hpp>
#include <vp/types.hpp>

#include <vp/dependency_graph.hpp>

using namespace vp::types;

int main(i32 argc, char *argv[]) try {
    vp::DefaultErrorReporter errReporter;
    vp::ErrorHandler::reporter = &errReporter;

    if (argc != 2) {
        vp::ErrorHandler::report<std::invalid_argument>(1, "Wrong number of arguments");
    }

    const auto filepath = std::string{argv[1]};
    std::ifstream fin { filepath };
    if (not fin.is_open()) {
        vp::ErrorHandler::report<std::runtime_error>(1, "Could not Open a file");
    }

    auto interpreter = vp::Interpreter(fin);
    interpreter.interpret();

    return 0;
} catch (std::exception &e) {
    fmt::println(stderr, "{}", e.what());
    return EXIT_FAILURE;
}
