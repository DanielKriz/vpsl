/// @file test_main.cpp
///
/// This file contains the minimal main needed to run doctest tests and
/// assertions, it may be used in the future to provide more sofisticated
/// feature testing and filtration.

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

int main(int argc, char *argv[]) {
    doctest::Context ctx;

    ctx.applyCommandLine(argc, argv);

    int res = ctx.run();
    if (ctx.shouldExit()) {
        return res;
    }
    return res;
}
