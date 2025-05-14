#include <doctest/doctest.h>

#include <vp/description/buffer_store.hpp>

using namespace vp::desc;

class BufferStoreFixture {
protected:
    BufferStore &store;
public:
    BufferStoreFixture() : store(BufferStore::getInstance()) {}
    ~BufferStoreFixture() { store.clear(); }
};

TEST_SUITE("Buffer Store") {

TEST_CASE("Simple construction does not throw") {
    CHECK_NOTHROW(BufferStore::getInstance());
}

TEST_CASE_FIXTURE(
    BufferStoreFixture,
    "TEXT"
) {
}

}
