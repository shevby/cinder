#include "Gzip.h"
#include "HttpRequest.h"
#include "LocationMapStateShort.h"
#include "utils.h"

#include <cstring>

#include <catch2/catch_test_macros.hpp>

std::string merge_lines(const std::vector<std::string> &lines) {
    return join(lines, "\n");
}

TEST_CASE("Adler-32 checksum", "[Compression]") {
    REQUIRE(adler_32_checksum("I like cats") == "\x15\x77\x03\xDA");
}

TEST_CASE("CRC-32 checksum", "[Compression]") {
    REQUIRE(crc32("I like cats") == "\x0E\xBC\x90\x0A");
}

TEST_CASE("Simple request", "[WebServer]") {
    char request[] = "GET /";
    HttpRequest r(request, strlen(request));
    REQUIRE(r.first_line == "GET /");
    REQUIRE(r.headers == std::vector<std::string>());
    REQUIRE(r.body == "");
}

TEST_CASE("Simple request with newline", "[WebServer]") {
    char request[] = "GET /\n";
    HttpRequest r(request, strlen(request));
    REQUIRE(r.first_line == "GET /");
    REQUIRE(r.headers == std::vector<std::string>());
    REQUIRE(r.body == "");
}

TEST_CASE("Simple request with 2 newlines", "[WebServer]") {
    char request[] = "GET /\n\n";
    HttpRequest r(request, strlen(request));
    REQUIRE(r.first_line == "GET /");
    REQUIRE(r.headers == std::vector<std::string>());
    REQUIRE(r.body == "");
}

TEST_CASE("Request with body", "[WebServer]") {
    char request[] = "GET /\n\nHello";
    HttpRequest r(request, strlen(request));
    REQUIRE(r.first_line == "GET /");
    REQUIRE(r.headers == std::vector<std::string>());
    REQUIRE(r.body == "Hello");
}

TEST_CASE("Request with body with newline", "[WebServer]") {
    char request[] = "GET /\n\nHello\n";
    HttpRequest r(request, strlen(request));
    REQUIRE(r.first_line == "GET /");
    REQUIRE(r.headers == std::vector<std::string>());
    REQUIRE(r.body == "Hello\n");
}

TEST_CASE("Request with body with multiple newlines", "[WebServer]") {
    char request[] = "GET /\n\nHello\n\n";
    HttpRequest r(request, strlen(request));
    REQUIRE(r.first_line == "GET /");
    REQUIRE(r.headers == std::vector<std::string>());
    REQUIRE(r.body == "Hello\n\n");
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
