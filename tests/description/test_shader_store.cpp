#include <doctest/doctest.h>

#include <vp/description/shader_code.hpp>
#include <vp/description/shader_code_store.hpp>

using namespace vp::desc;

class ShaderCodeStoreFixture {
protected:
    ShaderCodeStore &store;
public:
    ShaderCodeStoreFixture() : store(ShaderCodeStore::getInstance()) {}
    ~ShaderCodeStoreFixture() { store.clear(); }
};

TEST_SUITE("Shader Store") {

TEST_CASE("Simple constructor") {
    CHECK_NOTHROW(ShaderCodeStore::getInstance());
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "It is possible to emplace shader objects to the store"
) {
    auto *obj = store.emplace("shader");
    CHECK(std::is_same_v<decltype(obj), vp::ShaderCode *>);
    CHECK(obj->isEmpty());
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Retrieval of shader from the store"
) {
    auto *obj = store.emplace("shader");
    auto *ref = store.getShaderCode("shader");
    CHECK(obj == ref);
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Retrieval of shader from the store with an operator"
) {
    auto *obj = store.emplace("shader");
    auto *ref = store["shader"];
    CHECK(obj == ref);
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Retrieval of shader from the const store"
) {
    auto *obj = store.emplace("shader");
    const auto &storeRef = store;
    const auto *ref = storeRef.getShaderCode("shader");
    CHECK(obj == ref);
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Retrieval of shader from the const store with an operator"
) {
    auto *obj = store.emplace("shader");
    const auto &storeRef = store;
    const auto &ref = storeRef["shader"];
    CHECK(obj == ref);
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "It is possible to insert an already existing object into the store"
) {
    vp::ShaderCode obj;
    store.insert("shader", obj);
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Checking that store contains a shader"
) {
    store.emplace("shader");
    CHECK(store.contains("shader"));
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Checking that contains returns false when shader does not exist"
) {
    CHECK_FALSE(store.contains("shader"));
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Adding dependencies to a shader that does not exist results in failure"
) {
    std::vector<std::string> others {};
    CHECK_THROWS(store.addDependencies("non_existent", others));
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Adding dependencies to a shader add them to the store"
) {
    store.emplace("shader");
    std::vector<std::string> others {"A", "B"};
    CHECK_NOTHROW(store.addDependencies("shader", others));
    CHECK(store.contains("shader"));
    CHECK(store.contains("A"));
    CHECK(store.contains("B"));
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Insertion of already present shader does nothing"
) {
    auto *code = store.emplace("shader");
    CHECK(store.emplace("shader") == code);
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Addition of dependencies to an empty shader does nothing"
) {
    store.addDependencies("", {"other"});
    CHECK_FALSE(store.contains("other"));
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "It is possible to emplace unnamed shaders"
) {
    auto *code = store.emplaceUnnamed();
    CHECK(std::is_same_v<decltype(code), vp::ShaderCode *>);
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "it is possible to compose all shaders"
) {
    auto *named = store.emplace("shader");
    auto *unnamed = store.emplaceUnnamed();
    CHECK_FALSE(named->isComposed());
    CHECK_FALSE(unnamed->isComposed());
    store.composeAllShaders();
    CHECK(named->isComposed());
    CHECK(unnamed->isComposed());
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Composition of shaders fails if there are cyclic dependencies"
) {
    store.addDependencies("A", {"B"});
    store.addDependencies("B", {"A"});
    CHECK_THROWS(store.composeAllShaders());
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Getting a shader that is not in the store throws"
) {
    CHECK_THROWS(store.getShaderCode("unknown"));
}

TEST_CASE_FIXTURE(
    ShaderCodeStoreFixture,
    "Getting a shader that is not in the const store throws"
) {
    const auto &constStore = store;
    CHECK_THROWS(constStore.getShaderCode("unknown"));
}

}
