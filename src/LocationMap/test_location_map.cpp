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

TEST_CASE("LZ77 match: no match at the beginning", "[Compression]") {
    auto match = find_max_length_match("ABCDEF", 0, 0);
    REQUIRE(match.length == 0);
    match = find_max_length_match("AAAAAAA", 0, 0);
    REQUIRE(match.length == 0);
}

TEST_CASE("LZ77 match: from index 1", "[Compression]") {
    auto match = find_max_length_match("AAAAAAA", 1, 0);
    REQUIRE(match.length == 1);
    REQUIRE(match.absolute_pos == 0);
    match = find_max_length_match("ABCDEF", 1, 0);
    REQUIRE(match.length == 0);
}

TEST_CASE("LZ77 match: from the end", "[Compression]") {
    auto match = find_max_length_match("AAAAAAA", 6, 0);
    REQUIRE(match.length == 1);
    REQUIRE(match.absolute_pos == 0);
    match = find_max_length_match("ABCDEF", 5, 0);
    REQUIRE(match.length == 0);
}

TEST_CASE("LZ77 match: avoid overlapping with itself", "[Compression]") {
    auto match = find_max_length_match("AAAAAAA", 3, 0);
    REQUIRE(match.length == 3);
    REQUIRE(match.absolute_pos == 0);
}

TEST_CASE("LZ77 match: take longest match", "[Compression]") {
    auto match = find_max_length_match("ABCD" "ABCDEF" "ABCD" "ABCDEFGH", 14, 0);
    REQUIRE(match.length == 6);
    REQUIRE(match.absolute_pos == 4);
}

TEST_CASE("to_lz77_entries", "[Compression]") {
    auto res = to_lz77_entries("A", 100, 3);
    std::vector<lz77_entry> expected = {
        lz77_entry('A'),
    };
    CHECK(res == expected);

    res = to_lz77_entries("AAA", 100, 3);
    expected = {
        lz77_entry('A'),
        lz77_entry('A'),
        lz77_entry('A'),
    };
    CHECK(res == expected);

    res = to_lz77_entries("ABCD_ABCD", 100, 3);
    expected = {
        lz77_entry('A'),
        lz77_entry('B'),
        lz77_entry('C'),
        lz77_entry('D'),
        lz77_entry('_'),
        lz77_entry(5, 4),
    };
    CHECK(res == expected);

    res = to_lz77_entries("ABCD_ABCD", 4, 3);
    expected = {
        lz77_entry('A'),
        lz77_entry('B'),
        lz77_entry('C'),
        lz77_entry('D'),
        lz77_entry('_'),
        lz77_entry('A'),
        lz77_entry('B'),
        lz77_entry('C'),
        lz77_entry('D'),
    };
    CHECK(res == expected);
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
