#include <doctest/doctest.h>

#include <sstream>

#include <vp/description/buffer_description.hpp>

using namespace vp::desc;

TEST_SUITE("Buffer Description") {

TEST_CASE("Simple construction does not throw") {
    CHECK_NOTHROW(BufferDescription{1, 1});
}

TEST_CASE("It is not possible to create a buffer with 0 size") {
    CHECK_THROWS(BufferDescription{0, 1});
}

TEST_CASE("It is not possible to copy buffers") {
    auto buf1 = BufferDescription{1, 1};
    CHECK_NOTHROW(buf1 = BufferDescription{2,2});
}

TEST_CASE("Comparing two same buffers yields true") {
    CHECK(BufferDescription{1, 1} == BufferDescription{1, 1});
}

TEST_CASE("It is possible to compare two same instances of buffers") {
    CHECK(BufferDescription{1, 1} == BufferDescription{1, 1});
}

TEST_CASE("Buffer string representation") {
    std::stringstream ss;
    ss << BufferDescription{1024, 0};
    CHECK(ss.str() == "Buffer(1024, 0)");
}

}
