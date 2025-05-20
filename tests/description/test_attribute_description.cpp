#include <doctest/doctest.h>

#include <vp/description/attribute_description.hpp>

using namespace vp;
using namespace vp::desc;

TEST_SUITE("Attribute Description") {

TEST_CASE("Copy construction") {

    AttributeDescription desc;
    desc.addAttribute(AttributeType::Position, 1);
    desc.addAttribute(AttributeType::Normal, 2);
    desc.addAttribute(AttributeType::Bitangent, 3);

    AttributeDescription copy = desc;
    const auto &attrs = copy.getAttributes();
    CHECK(attrs[0].type == AttributeType::Position);
    CHECK(attrs[0].location == 1);
    CHECK(attrs[1].type == AttributeType::Normal);
    CHECK(attrs[1].location == 2);
    CHECK(attrs[2].type == AttributeType::Bitangent);
    CHECK(attrs[2].location == 3);
}

TEST_CASE("Position string representation") {
    std::stringstream ss;
    ss << AttributeType::Position;
    CHECK(ss.str() == "Position");
}

TEST_CASE("Normal string representation") {
    std::stringstream ss;
    ss << AttributeType::Normal;
    CHECK(ss.str() == "Normal");
}

TEST_CASE("UV string representation") {
    std::stringstream ss;
    ss << AttributeType::UV;
    CHECK(ss.str() == "UV");
}

TEST_CASE("Tangent string representation") {
    std::stringstream ss;
    ss << AttributeType::Tangent;
    CHECK(ss.str() == "Tangent");
}

TEST_CASE("Bitangent string representation") {
    std::stringstream ss;
    ss << AttributeType::Bitangent;
    CHECK(ss.str() == "Bitangent");
}

TEST_CASE("Getting the count of elements in position") {
    CHECK(Attribute::elementCountFromType(AttributeType::Position) == 3);
}

TEST_CASE("Getting the count of elements in normal") {
    CHECK(Attribute::elementCountFromType(AttributeType::Normal) == 3);
}

TEST_CASE("Getting the count of elements in UV") {
    CHECK(Attribute::elementCountFromType(AttributeType::UV) == 2);
}

TEST_CASE("Getting the count of elements in tangent") {
    CHECK(Attribute::elementCountFromType(AttributeType::Tangent) == 3);
}

TEST_CASE("Getting the count of elements in bitangent") {
    CHECK(Attribute::elementCountFromType(AttributeType::Bitangent) == 3);
}

TEST_CASE("Getting the offset of position") {
    CHECK(Attribute::offsetFromType(AttributeType::Position) == 0 * sizeof(float));
}

TEST_CASE("Getting the offset of normal") {
    CHECK(Attribute::offsetFromType(AttributeType::Normal) == 3 * sizeof(float));
}

TEST_CASE("Getting the offset of position") {
    CHECK(Attribute::offsetFromType(AttributeType::UV) == 6 * sizeof(float));
}

TEST_CASE("Getting the offset of tangent") {
    CHECK(Attribute::offsetFromType(AttributeType::Tangent) == 8 * sizeof(float));
}

TEST_CASE("Getting the offset of bitangent") {
    CHECK(Attribute::offsetFromType(AttributeType::Bitangent) == 11 * sizeof(float));
}

TEST_CASE("String representation of an attribute") {
    std::stringstream ss;
    ss << Attribute(AttributeType::Position, 0);
    CHECK(ss.str() == "Attribute(Position, 0)");
}

TEST_CASE("String representation of an attribute description") {
    std::stringstream ss;
    AttributeDescription attrDesc{};
    attrDesc.addAttribute(AttributeType::Position, 0);
    ss << attrDesc;
    CHECK(ss.str() == "AttributeDescription(Attribute(Position, 0))");
}

}
