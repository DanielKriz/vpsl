#include <iostream>
#include <sstream>

#include <doctest/doctest.h>

#include <vp/description/options.hpp>

using namespace vp;
using namespace vp::gl;

TEST_SUITE("Options") {

TEST_CASE("Default construction does not throw") {
    CHECK_NOTHROW(std::ignore = Options{});
}

TEST_CASE("Options default values") {
    auto opts = Options{};
    CHECK(opts.isDepthTestEnabled == false);
    CHECK(opts.isFaceCullingEnabled == false);
    CHECK(opts.isBlendingEnabled == false);
    CHECK(opts.frontFacePolygonMode == PolygonMode::Fill);
    CHECK(opts.backFacePolygonMode == PolygonMode::Fill);
    CHECK(opts.cullingMode == CullingMode::Back);
    CHECK(opts.frontFaceMode == FrontFaceMode::CCW);
    CHECK(opts.depthFunction == DepthFunction::Less);
    CHECK(opts.srcBlendFactor == BlendingFactor::One);
    CHECK(opts.dstBlendFactor == BlendingFactor::Zero);
}

TEST_CASE("It is possible to copy options") {
    auto opts = Options{};
    CHECK_NOTHROW(opts = opts);
}

TEST_CASE("It is possible to get options representation") {
    std::stringstream ss;
    ss << Options{};
    CHECK(ss.str() ==
R"(Is depth test enabled: false
Is blending enabled: false
Is face culling enabled: false
Front Face Polygon Mode: 2
Back Face Polygon Mode: 2
Culling Mode: 1
Front Face Mode: 1
Depth Function: 1
Source Blend Factor: 1
Destination Blend Factor: 0
)");
}

TEST_CASE("It is possible to compare two sets of options") {
    SUBCASE("fresh constructions are the same") {
        const auto opts1 = Options{};
        const auto opts2 = Options{};
        CHECK(opts1 == opts2);
    }
    SUBCASE("equal if comparing copies") {
        const auto opts1 = Options{};
        const auto opts2 = opts1;
        CHECK(opts1 == opts2);
    }
    SUBCASE("non equal if not the same") {
        const auto opts1 = Options{};
        auto opts2 = Options{};
        SUBCASE("Is depth test enabled") {
            opts2.isDepthTestEnabled = true;
            CHECK_FALSE(opts1 == opts2);
        }
        SUBCASE("Is blending enabled") {
            opts2.isBlendingEnabled = true;
            CHECK_FALSE(opts1 == opts2);
        }
        SUBCASE("Is face culling enabled") {
            opts2.isFaceCullingEnabled = true;
            CHECK_FALSE(opts1 == opts2);
        }
        SUBCASE("Front face polygon mode") {
            opts2.frontFacePolygonMode = PolygonMode::Point;
            CHECK_FALSE(opts1 == opts2);
        }
        SUBCASE("Back face polygon mode") {
            opts2.backFacePolygonMode = PolygonMode::Point;
            CHECK_FALSE(opts1 == opts2);
        }
        SUBCASE("Culling mode") {
            opts2.cullingMode = CullingMode::Front;
            CHECK_FALSE(opts1 == opts2);
        }
        SUBCASE("Front face mode") {
            opts2.frontFaceMode = FrontFaceMode::CW;
            CHECK_FALSE(opts1 == opts2);
        }
        SUBCASE("Depth Function") {
            opts2.depthFunction = DepthFunction::Never;
            CHECK_FALSE(opts1 == opts2);
        }
        SUBCASE("Source Blend Factor") {
            opts2.srcBlendFactor = BlendingFactor::OneMinusSourceAlpha;
            CHECK_FALSE(opts1 == opts2);
        }
        SUBCASE("Destination Blend Factor") {
            opts2.dstBlendFactor = BlendingFactor::OneMinusSourceAlpha;
            CHECK_FALSE(opts1 == opts2);
        }
    }
}

}
