#include <doctest/doctest.h>

#include <vp/shader_code_store.hpp>

using namespace vp;

TEST_SUITE("Shader Store") {

TEST_CASE("Simple constructor") {
    CHECK_NOTHROW(ShaderCodeStore{});
}

TEST_CASE("It is possible to emplace shader objects to the store") {
    auto store = ShaderCodeStore{};
    auto *obj = store.emplace("shader");
    CHECK(std::is_same_v<decltype(obj), ShaderObject *>);
    CHECK(obj->isEmpty());
}

TEST_CASE("Retrieval of shader from the store") {
    auto store = ShaderCodeStore{};
    auto *obj = store.emplace("shader");
    auto *ref = store.getShaderObject("shader");
    CHECK(obj == ref);
}

TEST_CASE("Retrieval of shader from the store with an operator") {
    auto store = ShaderCodeStore{};
    auto *obj = store.emplace("shader");
    auto *ref = store["shader"];
    CHECK(obj == ref);
}

TEST_CASE("Retrieval of shader from the const store") {
    auto store = ShaderCodeStore{};
    auto *obj = store.emplace("shader");
    const auto &storeRef = store;
    const auto *ref = storeRef.getShaderObject("shader");
    CHECK(obj == ref);
}

TEST_CASE("Retrieval of shader from the const store with an operator") {
    auto store = ShaderCodeStore{};
    auto *obj = store.emplace("shader");
    const auto &storeRef = store;
    const auto &ref = storeRef["shader"];
    CHECK(obj == ref);
}

TEST_CASE("It is possible to insert an already existing object into the store") {
    auto store = ShaderCodeStore{};
    ShaderObject obj;
    store.insert("shader", obj);
}

}
