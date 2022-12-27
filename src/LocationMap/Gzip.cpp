#include "Gzip.h"

static std::string unit32_to_string(uint32_t num) {
    return std::string()
         + static_cast<char>(num >> 24)
         + static_cast<char>((num >> 16) & 0xFF)
         + static_cast<char>((num >> 8) & 0xFF)
         + static_cast<char>(num & 0xFF);
}

std::string adler_32_checksum(const std::string &content) {
    constexpr uint32_t MOD_ADLER_32 = 65521;

    uint32_t A = 1;
    uint32_t B = 0;

    for (char const &ch: content) {
        A += static_cast<unsigned char>(ch) % MOD_ADLER_32;
        B += A % MOD_ADLER_32;
    }

    return unit32_to_string((B << 16) | A);
}

std::string deflate_payload(const std::string &content) {
}

std::string deflate(const std::string &content) {
}

std::string crc32(const std::string &content) {
}

std::string gzip_compress(const std::string &content) {
    const std::string MAGIC = "\x1F\x8B";
    const std::string COMPRESSION_METHOD = "\x08"; // 0x08 = DEFLATE
    std::string flags = "\0";
    const std::string TIMESTAMP = "\x00\x00\x00\x00";
    std::string compression_flags = "\0";
    const std::string OS_ID = "\xFF"; // 0xFF = unknown

    std::string header = MAGIC + COMPRESSION_METHOD + flags + TIMESTAMP + compression_flags + OS_ID;

    std::string res = header + deflate_payload(content) + crc32(content) + unit32_to_string(content.size());
    return res;
}
