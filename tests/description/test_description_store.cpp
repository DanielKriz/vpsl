#include <doctest/doctest.h>

#include <vp/description/description_store.hpp>
#include <vp/types.hpp>

using namespace vp;
using namespace vp::desc;
using namespace vp::types;

TEST_SUITE("Description Store") {

TEST_CASE("It is possible to create a description store") {
    // it is not specified that the store has to provide storage only to some description
    // type. Therefore tests can be done a simple integer.
    CHECK_NOTHROW(DescriptionStore<int>());
}

TEST_CASE("It is possible to emplace new entries to the store") {
    auto store = DescriptionStore<int>();
    int *pValue = store.emplace("new_value");
    CHECK(pValue != nullptr);
}

TEST_CASE("It is possible to check that store contains some value") {
    auto store = DescriptionStore<int>();
    SUBCASE("Return false when it doesn't") {
        CHECK_FALSE(store.contains("not_found"));
    }
    SUBCASE("Returns true when it does") {
        store.emplace("found");
        CHECK(store.contains("found"));
    }
}

TEST_CASE("It is possible to insert new entries to the store") {
    auto store = DescriptionStore<int>();
    int value = 1;
    CHECK_NOTHROW(store.insert("value", value));
    CHECK(store.contains("value"));
}

TEST_CASE("It is possible to retrieve a value from the store") {
    auto store = DescriptionStore<int>();
    int value = 1;
    CHECK_NOTHROW(store.insert("value", value));
    auto retrieved = store.getDescription("value");
    CHECK(value == retrieved);
}

TEST_CASE("It is possible to retrieve a value from the const store") {
    auto store = DescriptionStore<int>();
    int value = 1;
    CHECK_NOTHROW(store.insert("value", value));
    const auto &const_ref = store;
    auto retrieved = const_ref.getDescription("value");
    CHECK(value == retrieved);
}

TEST_CASE("It is possible to retrieve a value from the store with an operator") {
    auto store = DescriptionStore<int>();
    int value = 1;
    CHECK_NOTHROW(store.insert("value", value));
    auto retrieved = store["value"];
    CHECK(value == retrieved);
}

TEST_CASE("It is possible to retrieve a value from the const store with an operator") {
    auto store = DescriptionStore<int>();
    int value = 1;
    CHECK_NOTHROW(store.insert("value", value));
    const auto &const_ref = store;
    auto retrieved = const_ref["value"];
    CHECK(value == retrieved);
}

TEST_CASE("Inserted value is only a copy") {
    auto store = DescriptionStore<int>();
    int value = 1;
    CHECK_NOTHROW(store.insert("value", value));
    CHECK(store.contains("value"));
    value = 0;
    CHECK(store["value"] != value);
}

TEST_CASE("Value is not present after clearing") {
    auto store = DescriptionStore<int>();
    const int value = 1;
    store.insert("value", value);
    CHECK(store.contains("value"));
    store.clear();
    CHECK_FALSE(store.contains("value"));
}

}
