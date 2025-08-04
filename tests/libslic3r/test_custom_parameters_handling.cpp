#include <catch2/catch_test_macros.hpp>
#include "libslic3r/CustomParametersHandling.hpp"

using namespace Slic3r;

TEST_CASE("CustomParametersHandling tests", "[CustomParametersHandling]")
{
    SECTION("Valid simple values") {
        std::string json_str = R"({
            "string_param": "hello",
            "int_param": 42,
            "double_param": 3.14,
            "bool_param": true,
            "null_param": null
        })";
        auto result = parse_custom_parameters(json_str);
        REQUIRE(result.has_value());
        auto& values = *result;
        REQUIRE(values.size() == 5);
        REQUIRE(std::get<std::string>(values["string_param"]) == "hello");
        REQUIRE(std::get<int>(values["int_param"]) == 42);
        REQUIRE(std::get<double>(values["double_param"]) == 3.14);
        REQUIRE(std::get<bool>(values["bool_param"]) == true);
        REQUIRE(std::holds_alternative<std::monostate>(values["null_param"]));
    }

    SECTION("Invalid JSON") {
        std::string json_str = R"({ "param": "value" )"; // Incomplete
        auto result = parse_custom_parameters(json_str);
        REQUIRE_FALSE(result.has_value());
    }

    SECTION("Not a JSON object") {
        std::string json_str = R"([1, 2, 3])";
        auto result = parse_custom_parameters(json_str);
        REQUIRE_FALSE(result.has_value());
    }

    SECTION("Heterogeneous array") {
        std::string json_str = R"({ "mixed_vec": ["a", 1, true] })";
        auto result = parse_custom_parameters(json_str);
        REQUIRE_FALSE(result.has_value());
    }

    SECTION("Empty array") {
        std::string json_str = R"({ "empty_vec": [] })";
        auto result = parse_custom_parameters(json_str);
        REQUIRE_FALSE(result.has_value());
    }

    SECTION("Unsupported type") {
        std::string json_str = R"({ "object_param": { "a": 1 } })";
        auto result = parse_custom_parameters(json_str);
        REQUIRE_FALSE(result.has_value());
    }
    
    SECTION("Empty input") {
        std::string json_str = "";
        auto result = parse_custom_parameters(json_str);
        REQUIRE(result.has_value());
        REQUIRE(result->empty());
    }

    SECTION("Empty JSON object") {
        std::string json_str = "{}";
        auto result = parse_custom_parameters(json_str);
        REQUIRE(result.has_value());
        REQUIRE(result->empty());
    }
}