#include <doctest/doctest.h>
#include <vp/utils.hpp>

using namespace vp;

TEST_SUITE_BEGIN("Utils");

TEST_CASE("left trim") {
    SUBCASE("does nothing on an empty string") {
        std::string line{};
        const std::string lineCopy = line;
        utils::ltrim(line);
        CHECK(line == lineCopy);
    }
    SUBCASE("does nothing on trimmed string") {
        std::string line{"trimmed"};
        const std::string lineCopy = line;
        utils::ltrim(line);
        CHECK(line == lineCopy);
    }
    SUBCASE("trims only from the left") {
        std::string line{"trimmed      "};
        const std::string lineCopy = line;
        utils::ltrim(line);
        CHECK(line == lineCopy);
    }
    SUBCASE("successfully trims valid target") {
        std::string line{"     trimmed"};
        utils::ltrim(line);
        CHECK(line == "trimmed");
    }
    SUBCASE("double trimming does nothing") {
        std::string line{"     trimmed"};
        utils::ltrim(line);
        const std::string lineCopy = line;
        utils::ltrim(line);
        CHECK(line == lineCopy);
    }
}

TEST_CASE("right trim") {
    SUBCASE("does nothing on an empty string") {
        std::string line{};
        const std::string lineCopy = line;
        utils::rtrim(line);
        CHECK(line == lineCopy);
    }
    SUBCASE("does nothing on trimmed string") {
        std::string line{"trimmed"};
        const std::string lineCopy = line;
        utils::rtrim(line);
        CHECK(line == lineCopy);
    }
    SUBCASE("trims only from the right") {
        std::string line{"       trimmed"};
        const std::string lineCopy = line;
        utils::rtrim(line);
        CHECK(line == lineCopy);
    }
    SUBCASE("successfully trims valid target") {
        std::string line{"trimmed       "};
        utils::rtrim(line);
        CHECK(line == "trimmed");
    }
    SUBCASE("double trimming does nothing") {
        std::string line{"trimmed      "};
        utils::rtrim(line);
        const std::string lineCopy = line;
        utils::rtrim(line);
        CHECK(line == lineCopy);
    }
}

TEST_CASE("both-way trim") {
    SUBCASE("does nothing on an empty string") {
        std::string line{};
        const std::string lineCopy = line;
        utils::trim(line);
        CHECK(line == lineCopy);
    }
    SUBCASE("does nothing on trimmed string") {
        std::string line{"trimmed"};
        const std::string lineCopy = line;
        utils::trim(line);
        CHECK(line == lineCopy);
    }
    SUBCASE("can trim only from the right") {
        std::string line{"trimmed       "};
        utils::trim(line);
        CHECK(line == "trimmed");
    }
    SUBCASE("can trim only from the left") {
        std::string line{"       trimmed"};
        utils::trim(line);
        CHECK(line == "trimmed");
    }
    SUBCASE("successfully trims valid target") {
        std::string line{"       trimmed       "};
        utils::trim(line);
        CHECK(line == "trimmed");
    }
    SUBCASE("double trimming does nothing") {
        std::string line{"       trimmed      "};
        utils::trim(line);
        const std::string lineCopy = line;
        utils::trim(line);
        CHECK(line == lineCopy);
    }
}

TEST_CASE("both-way copy trim") {
    SUBCASE("does nothing on an empty string") {
        std::string line{};
        const std::string lineCopy{line};
        const std::string trimmedLine = utils::trimCopy(line);
        CHECK(line == trimmedLine);
        REQUIRE(line == lineCopy);
    }
    SUBCASE("does nothing on trimmed string") {
        std::string line{"trimmed"};
        const std::string lineCopy = line;
        const std::string trimmedLine = utils::trimCopy(line);
        CHECK(line == trimmedLine);
        REQUIRE(line == lineCopy);
    }
    SUBCASE("successfully trims valid target") {
        std::string line{"     target      "};
        const std::string lineCopy = line;
        const std::string trimmedLine = utils::trimCopy(line);
        CHECK("target" == trimmedLine);
        REQUIRE(line == lineCopy);
    }
}

TEST_SUITE_END();
