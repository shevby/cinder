#include "Gzip.h"
#include "HttpRequest.h"
#include "LocationMapStateShort.h"
#include "utils.h"

#include <cstring>
#include <iostream>

#define TEST_EQUAL(first, second) \
    if (first != second) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << #first << " != " << #second << "\n"; \
        std::cerr << #first << " == " << first << "\n"; \
        std::cerr << #second << " == " << second << "\n"; \
        std::cerr << "----------------------------\n"; \
    }

#define TEST_EQUAL_VECTOR(first, second) \
    if (first != second) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << #first << " != " << #second << "\n"; \
        std::cerr << "length of " #first " = " << first.size() << "\n"; \
        std::cerr << "length of " #second " = " << second.size() << "\n"; \
        std::cerr << "----------------------------\n"; \
    }

#define TOKEN_COMBINE(A, B) A ## B
#define TOKEN_COMBINE2(A, B) TOKEN_COMBINE(A, B)
#define TEST_CASE(A, B) void TOKEN_COMBINE2(catch2_test_function_imitation_, __LINE__)()
#define REQUIRE(X) TEST_EQUAL(X, true)

std::string merge_lines(const std::vector<std::string> &lines) {
    return join(lines, "\n");
}

int main() {
    TEST_EQUAL(adler_32_checksum("I like cats"), "\x15\x77\x03\xDA");

    {
        char request[] = "GET /";
        HttpRequest r(request, strlen(request));
        TEST_EQUAL(r.first_line, "GET /");
        TEST_EQUAL_VECTOR(r.headers, std::vector<std::string>());
        TEST_EQUAL(r.body, "");
    }

    {
        char request[] = "GET /\n";
        HttpRequest r(request, strlen(request));
        TEST_EQUAL(r.first_line, "GET /");
        TEST_EQUAL_VECTOR(r.headers, std::vector<std::string>());
        TEST_EQUAL(r.body, "");
    }

    {
        char request[] = "GET /\n\n";
        HttpRequest r(request, strlen(request));
        TEST_EQUAL(r.first_line, "GET /");
        TEST_EQUAL_VECTOR(r.headers, std::vector<std::string>());
        TEST_EQUAL(r.body, "");
    }

    {
        char request[] = "GET /\n\nHello";
        HttpRequest r(request, strlen(request));
        TEST_EQUAL(r.first_line, "GET /");
        TEST_EQUAL_VECTOR(r.headers, std::vector<std::string>());
        TEST_EQUAL(r.body, "Hello");
    }

    {
        char request[] = "GET /\n\nHello\n";
        HttpRequest r(request, strlen(request));
        TEST_EQUAL(r.first_line, "GET /");
        TEST_EQUAL_VECTOR(r.headers, std::vector<std::string>());
        TEST_EQUAL(r.body, "Hello\n");
    }

    {
        char request[] = "GET /\n\nHello\n\n";
        HttpRequest r(request, strlen(request));
        TEST_EQUAL(r.first_line, "GET /");
        TEST_EQUAL_VECTOR(r.headers, std::vector<std::string>());
        TEST_EQUAL(r.body, "Hello\n\n");
    }

#include "/tmp/test_location_map.inc"
}

TEST_CASE("CreatureShortState must produce valid JSON", "[CreatureShortState]") {
    CreatureShortState creature;
    creature.type = CreatureType::Rabbit;
    REQUIRE(is_valid_json(merge_lines(creature.to_json_lines(JsonConfig()))));
}

TEST_CASE("LocationTileShortState must produce valid JSON", "[LocationTileShortState]") {
    LocationTileShortState tile;
    REQUIRE(is_valid_json(merge_lines(tile.to_json_lines(JsonConfig()))));
}

TEST_CASE("LocationMapShortState must produce valid JSON", "[LocationMapShortState]") {
    LocationMapShortState map;
    REQUIRE(is_valid_json(merge_lines(map.to_json_lines(JsonConfig()))));
}
