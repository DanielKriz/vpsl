#include <doctest/doctest.h>

#include <vp/description/shader_code.hpp>
#include <vp/description/shader_code_store.hpp>

using namespace vp::desc;

TEST_SUITE("Shader Store") {

TEST_CASE("Simple constructor") {
    CHECK_NOTHROW(ShaderCodeStore{});
}

TEST_CASE("It is possible to emplace shader objects to the store") {
    auto store = ShaderCodeStore{};
    auto *obj = store.emplace("shader");
    CHECK(std::is_same_v<decltype(obj), vp::ShaderCode *>);
    CHECK(obj->isEmpty());
}

TEST_CASE("Retrieval of shader from the store") {
    auto store = ShaderCodeStore{};
    auto *obj = store.emplace("shader");
    auto *ref = store.getShaderCode("shader");
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
    const auto *ref = storeRef.getShaderCode("shader");
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
    vp::ShaderCode obj;
    store.insert("shader", obj);
}

TEST_CASE("Checking that store contains a shader") {
    auto store = ShaderCodeStore{};
    store.emplace("shader");
    CHECK(store.contains("shader"));
}

TEST_CASE("Checking that contains returns false when shader does not exist") {
    auto store = ShaderCodeStore{};
    CHECK_FALSE(store.contains("shader"));
}

TEST_CASE("Adding dependencies to a shader that does not exist results in failure") {
    auto store = ShaderCodeStore{};
    std::vector<std::string> others {};
    CHECK_THROWS(store.addDependencies("non_existent", others));
}

TEST_CASE("Adding dependencies to a shader add them to the store") {
    auto store = ShaderCodeStore{};
    store.emplace("shader");
    std::vector<std::string> others {"A", "B"};
    CHECK_NOTHROW(store.addDependencies("shader", others));
    CHECK(store.contains("shader"));
    CHECK(store.contains("A"));
    CHECK(store.contains("B"));
}

}
