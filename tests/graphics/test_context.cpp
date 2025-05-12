#include <doctest/doctest.h>

#include <vp/graphics/context_options.hpp>
#include <vp/types.hpp>
#include <vp/utils.hpp>

#include <string_view>

using namespace vp::gl;
using namespace vp::types;
using namespace vp::utils;
using namespace std::literals;

struct StubManager {
    u32 glEnableCalls;
    enum32 glEnableValue;
};

TEST_SUITE("Graphics") {

TEST_CASE("Casting string to a polygon mode") {
    SUBCASE("Point") {
        CHECK(mapStringToEnumKind<PolygonMode>("point"sv) == PolygonMode::Point);
    }
    SUBCASE("Line") {
        CHECK(mapStringToEnumKind<PolygonMode>("line"sv) == PolygonMode::Line);
    }
    SUBCASE("Fill") {
        CHECK(mapStringToEnumKind<PolygonMode>("fill"sv) == PolygonMode::Fill);
    }
}

TEST_CASE("Casting string to a culling mode") {
    SUBCASE("Front") {
        CHECK(mapStringToEnumKind<CullingMode>("front"sv) == CullingMode::Front);
    }
    SUBCASE("Back") {
        CHECK(mapStringToEnumKind<CullingMode>("back"sv) == CullingMode::Back);
    }
    SUBCASE("FrontAndBack") {
        CHECK(mapStringToEnumKind<CullingMode>("front_and_back"sv) == CullingMode::FrontAndBack);
    }
}

TEST_CASE("Casting string to a front face mode") {
    SUBCASE("CW") {
        CHECK(mapStringToEnumKind<FrontFaceMode>("cw"sv) == FrontFaceMode::CW);
    }
    SUBCASE("CCW") {
        CHECK(mapStringToEnumKind<FrontFaceMode>("ccw"sv) == FrontFaceMode::CCW);
    }
}

TEST_CASE("Casting string to a blending factor") {
    SUBCASE("Zero") {
        CHECK(mapStringToEnumKind<BlendingFactor>("zero"sv) == BlendingFactor::Zero);
    }
    SUBCASE("One") {
        CHECK(mapStringToEnumKind<BlendingFactor>("one"sv) == BlendingFactor::One);
    }
    SUBCASE("SourceColor") {
        CHECK(mapStringToEnumKind<BlendingFactor>("source_color"sv) == BlendingFactor::SourceColor);
    }
    SUBCASE("OneMinusSourceColor") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("one_minus_source_color"sv),
            BlendingFactor::OneMinusSourceColor
        );
    }
    SUBCASE("DestinationColor") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("destination_color"sv),
            BlendingFactor::DestinationColor
        );
    }
    SUBCASE("OneMinusDestinationColor") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("one_minus_destination_color"sv),
            BlendingFactor::OneMinusDestinationColor
        );
    }
    SUBCASE("SourceAlpha") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("source_alpha"sv),
            BlendingFactor::SourceAlpha
        );
    }
    SUBCASE("OneMinusSourceAlpha") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("one_minus_source_alpha"sv),
            BlendingFactor::OneMinusSourceAlpha
        );
    }
    SUBCASE("DestinationAlpha") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("destination_alpha"sv),
            BlendingFactor::DestinationAlpha
        );
    }
    SUBCASE("OneMinusDestinationAlpha") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("one_minus_destination_alpha"sv),
            BlendingFactor::OneMinusDestinationAlpha
        );
    }
    SUBCASE("ConstantColor") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("constant_color"s),
            BlendingFactor::ConstantColor
        );
    }
    SUBCASE("OneMinusConstantColor") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("one_minus_constant_color"sv),
            BlendingFactor::OneMinusConstantColor
        );
    }
    SUBCASE("ConstantAlpha") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("constant_alpha"sv),
            BlendingFactor::ConstantAlpha
        );
    }
    SUBCASE("OneMinusConstantAlpha") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("one_minus_constant_alpha"sv),
            BlendingFactor::OneMinusConstantAlpha
        );
    }
    SUBCASE("SourceAlphaSaturate") {
        CHECK_EQ(
            mapStringToEnumKind<BlendingFactor>("source_alpha_saturate"sv),
            BlendingFactor::SourceAlphaSaturate
        );
    }
}

TEST_CASE("Casting string to a front face mode") {
    SUBCASE("Never") {
        CHECK(mapStringToEnumKind<DepthFunction>("never"sv) == DepthFunction::Never);
    }
    SUBCASE("Less") {
        CHECK(mapStringToEnumKind<DepthFunction>("less"sv) == DepthFunction::Less);
    }
    SUBCASE("Less - short") {
        CHECK(mapStringToEnumKind<DepthFunction>("ls"sv) == DepthFunction::Less);
    }
    SUBCASE("Equal") {
        CHECK(mapStringToEnumKind<DepthFunction>("equal"sv) == DepthFunction::Equal);
    }
    SUBCASE("Equal - short") {
        CHECK(mapStringToEnumKind<DepthFunction>("eq"sv) == DepthFunction::Equal);
    }
    SUBCASE("LessEqual") {
        CHECK(mapStringToEnumKind<DepthFunction>("less_equal"sv) == DepthFunction::LessEqual);
    }
    SUBCASE("LessEqual - short") {
        CHECK(mapStringToEnumKind<DepthFunction>("leq"sv) == DepthFunction::LessEqual);
    }
    SUBCASE("Greater") {
        CHECK(mapStringToEnumKind<DepthFunction>("greater"sv) == DepthFunction::Greater);
    }
    SUBCASE("Greater - short") {
        CHECK(mapStringToEnumKind<DepthFunction>("gt"sv) == DepthFunction::Greater);
    }
    SUBCASE("GreaterEqual") {
        CHECK(mapStringToEnumKind<DepthFunction>("greater_equal"sv) == DepthFunction::GreaterEqual);
    }
    SUBCASE("GreaterEqual - short") {
        CHECK(mapStringToEnumKind<DepthFunction>("geq"sv) == DepthFunction::GreaterEqual);
    }
    SUBCASE("NotEqual") {
        CHECK(mapStringToEnumKind<DepthFunction>("not_equal"sv) == DepthFunction::NotEqual);
    }
    SUBCASE("NotEqual - short") {
        CHECK(mapStringToEnumKind<DepthFunction>("neq"sv) == DepthFunction::NotEqual);
    }
    SUBCASE("Always") {
        CHECK(mapStringToEnumKind<DepthFunction>("always"sv) == DepthFunction::Always);
    }
}

} // TEST_SUITE
