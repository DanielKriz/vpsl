#include <fstream>
#include <set>

#include <SDL3/SDL.h>
#include <fmt/core.h>

#include <vp/error_handling.hpp>
#include <vp/interpreter/interpreter.hpp>
#include <vp/interpreter/lexer.hpp>
#include <vp/interpreter/directive.hpp>
#include <vp/types.hpp>

#include <vp/dependency_graph.hpp>

using namespace vp::types;

int main(i32 argc, char *argv[]) try {
#if 1
#if 0
    auto lexer = vp::Lexer();
    auto tokens = lexer.scan("#pragma vp shader type(vertex)\n");

    for (const auto &token : tokens) {
        std::cout << token << std::endl;
    }

    fmt::println("finished");
#else

    vp::internal::DependencyGraph dp;
    dp.addNode("A");
    dp.addNode("B");
    dp.addNode("C");
    dp.addEdge("A", "B");
    dp.addEdge("B", "C");
    dp.addEdge("A", "C");

    fmt::println("Start of check");
    fmt::println("Is graph acyclic: {}", dp.isAcyclic());

#if 1
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
#endif

    auto interpreter = vp::Interpreter(fin);
    interpreter.interpret();

#endif
    return 0;
#else
        SDL_Window *window;                    // Declare a pointer
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL3 window",                  // window title
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        // Do game logic, present a frame, etc.
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
#endif
} catch (std::exception &e) {
    fmt::println(stderr, "{}", e.what());
    return EXIT_FAILURE;
}
