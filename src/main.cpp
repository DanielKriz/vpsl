#include <fstream>
#include <set>

#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include <vp/error_handling.hpp>
#include <vp/interpreter/interpreter.hpp>
#include <vp/interpreter/lexer.hpp>
#include <vp/interpreter/directive.hpp>
#include <vp/types.hpp>
#include <vp/engine/engine.hpp>

#include <vp/dependency_graph.hpp>

using namespace vp::types;

int main(i32 argc, char *argv[]) try {

#if NDEBUG
    spdlog::set_level(spdlog::level::info);
#else
    spdlog::set_level(spdlog::level::debug);
#endif

    vp::DefaultErrorReporter errReporter;
    vp::ErrorHandler::reporter = &errReporter;

    spdlog::info("Parsing input");
    if (argc != 2) {
        vp::ErrorHandler::report<std::invalid_argument>(1, "Wrong number of arguments");
    }

    const auto filepath = std::string{argv[1]};
    std::ifstream fin { filepath };
    if (not fin.is_open()) {
        vp::ErrorHandler::report<std::runtime_error>(1, "Could not Open a file");
    }

    spdlog::info("Starting the interpreter phase");
    auto interpreter = vp::Interpreter(fin);
    const auto execeutionSequenceDescription = interpreter.interpret();

    spdlog::info("Starting the engine phase");
    auto engine = vp::Engine();
    engine.handleExecutionSequence(execeutionSequenceDescription);
    engine.run();

    spdlog::info("Exiting correctly");
    return 0;
} catch (std::exception &e) {
    fmt::println(stderr, "{}: {}", fmt::styled("Error", fmt::fg(fmt::color::red)), e.what());
    return EXIT_FAILURE;
}
