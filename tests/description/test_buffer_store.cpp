#include <doctest/doctest.h>

#include <vp/description/buffer_store.hpp>

using namespace vp::desc;

TEST_SUITE("Buffer Store") {

TEST_CASE("Simple construction does not throw") {
    CHECK_NOTHROW(BufferStore{});
}

}
