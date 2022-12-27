#include "Gzip.h"

#include <iostream>

#define TEST_EQUAL(first, second) \
    if (first != second) { \
        std::cerr << #first << " != " << #second << "\n"; \
        std::cerr << #first << " == " << first << "\n"; \
        std::cerr << #second << " == " << second << "\n"; \
        std::cerr << "----------------------------\n"; \
    }

int main() {
    TEST_EQUAL(adler_32_checksum("I like cats"), "\x15\x77\x03\xDA");
}
