#include <doctest/doctest.h>

#include <vp/interpreter/shader_table.hpp>
#include <vp/builder_graph/shader_builder.hpp>

using namespace vp;

TEST_SUITE_BEGIN("Shader Table");

TEST_CASE("smoke test") {
    ShaderBuilder builder;
    ShaderTable::add("shader", builder);
}

TEST_SUITE_END();
