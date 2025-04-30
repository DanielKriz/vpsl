#include <doctest/doctest.h>

#include <vp/builder_graph/objects/shader_object.hpp>

using namespace vp;

TEST_SUITE("Shader Object") {

TEST_CASE("It is possible to construct a shader object") {
    CHECK_NOTHROW(ShaderObject{});
}

TEST_CASE("It is possible to get lines from a shader object") {
    ShaderObject obj{};
    const std::vector<std::string> &lines = obj.getLines();
    CHECK(lines.empty());
}

TEST_CASE("It is possible to add lines to a shader object") {
    ShaderObject obj{};
    obj.addLine("first line");
    const std::vector<std::string> &lines = obj.getLines();
    CHECK(not lines.empty());
    CHECK(lines[0] == "first line");
}

TEST_CASE("It is possible to prepend lines to a shader object") {
    ShaderObject obj{};
    obj.addLine("second line");

    const std::vector<std::string> prependLines = { "first line" };
    obj.prependLines(prependLines);

    const std::vector<std::string> &lines = obj.getLines();
    CHECK(not lines.empty());
    CHECK(lines[0] == "first line");
    CHECK(lines[1] == "second line");
}

TEST_CASE("It is possible to append lines to a shader object") {
    ShaderObject obj{};
    obj.addLine("first line");

    const std::vector<std::string> appendLines = { "second line" };
    obj.appendLines(appendLines);

    const std::vector<std::string> &lines = obj.getLines();
    CHECK(not lines.empty());
    CHECK(lines[0] == "first line");
    CHECK(lines[1] == "second line");
}

TEST_CASE("It is possible to prepend lines from other shader object") {
    ShaderObject obj1{};
    obj1.addLine("from first");
    ShaderObject obj2{};
    obj2.addLine("from second");

    obj1.prependLines(obj2);

    const std::vector<std::string> &lines = obj1.getLines();
    CHECK(not lines.empty());
    CHECK(lines[0] == "from second");
    CHECK(lines[1] == "from first");
}

TEST_CASE("It is possible to append lines from other shader object") {
    ShaderObject obj1{};
    obj1.addLine("from first");
    ShaderObject obj2{};
    obj2.addLine("from second");

    obj1.appendLines(obj2);

    const std::vector<std::string> &lines = obj1.getLines();
    CHECK(not lines.empty());
    CHECK(lines[0] == "from first");
    CHECK(lines[1] == "from second");
}

TEST_CASE("It is possible to add other object to append set") {
    ShaderObject obj1 {};
    ShaderObject obj2 {};

    obj1.addToAppendSet(obj2);
    CHECK(obj1.isInAppendSet(obj2));
}

TEST_CASE("It is possible to add other object to prepend set") {
    ShaderObject obj1 {};
    ShaderObject obj2 {};

    obj1.addToPrependSet(obj2);
    CHECK(obj1.isInPrependSet(obj2));
}

TEST_CASE("It is possible to compose a shader from append set") {
    ShaderObject obj1{};
    obj1.addLine("source line");
    ShaderObject obj2{};
    obj2.addLine("append line");

    obj1.addToAppendSet(obj2);
    obj1.compose();

    const std::vector<std::string> &lines = obj1.getLines();
    CHECK(not lines.empty());
    CHECK(lines[0] == "source line");
    CHECK(lines[1] == "append line");
}

TEST_CASE("Multiple insertion of the same shader to append set does not change the output") {
    ShaderObject obj1{};
    obj1.addLine("source line");
    ShaderObject obj2{};
    obj2.addLine("append line");

    obj1.addToAppendSet(obj2);
    obj1.addToAppendSet(obj2);
    obj1.compose();

    const std::vector<std::string> &lines = obj1.getLines();
    CHECK(not lines.empty());
    CHECK(lines.size() == 2);
    CHECK(lines[0] == "source line");
    CHECK(lines[1] == "append line");
}

TEST_CASE("It is possible to compose a shader from prepend set") {
    ShaderObject obj1{};
    obj1.addLine("source line");
    ShaderObject obj2{};
    obj2.addLine("prepend line");

    obj1.addToPrependSet(obj2);
    obj1.compose();

    const std::vector<std::string> &lines = obj1.getLines();
    CHECK(not lines.empty());
    CHECK(lines[0] == "prepend line");
    CHECK(lines[1] == "source line");
}

TEST_CASE("Multiple insertion of the same shader to prepend set does not change the output") {
    ShaderObject obj1{};
    obj1.addLine("source line");
    ShaderObject obj2{};
    obj2.addLine("prepend line");

    obj1.addToPrependSet(obj2);
    obj1.addToPrependSet(obj2);
    obj1.compose();

    const std::vector<std::string> &lines = obj1.getLines();
    CHECK(not lines.empty());
    CHECK(lines.size() == 2);
    CHECK(lines[0] == "prepend line");
    CHECK(lines[1] == "source line");
}

TEST_CASE("It is possible to compose a shader from append and prepend set") {
    ShaderObject obj1{};
    obj1.addLine("source line");
    ShaderObject obj2{};
    obj2.addLine("prepend line");
    ShaderObject obj3{};
    obj3.addLine("append line");

    obj1.addToPrependSet(obj2);
    obj1.addToAppendSet(obj3);
    obj1.compose();

    const std::vector<std::string> &lines = obj1.getLines();
    CHECK(not lines.empty());
    CHECK(lines[0] == "prepend line");
    CHECK(lines[1] == "source line");
    CHECK(lines[2] == "append line");
}

TEST_CASE("it is possible to create a source from shader object") {
    ShaderObject obj{};
    obj.addLine("first line");
    obj.addLine("second line");
    obj.addLine("third line");

    const std::string expected = "first line\nsecond line\nthird line\n";
    CHECK(obj.createSource() == expected);
}

}
