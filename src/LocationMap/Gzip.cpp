#include "Gzip.h"

std::string adler_32_checksum(const std::string &content) {
    constexpr uint32_t MOD_ADLER_32 = 65521;

    uint32_t A = 1;
    uint32_t B = 0;

    for (char const &ch: content) {
        A += static_cast<unsigned char>(ch) % MOD_ADLER_32;
        B += A % MOD_ADLER_32;
    }

    uint32_t res = (B << 16) | A;

    return std::string()
         + static_cast<char>(res >> 24)
         + static_cast<char>((res >> 16) & 0xFF)
         + static_cast<char>((res >> 8) & 0xFF)
         + static_cast<char>(res & 0xFF);
}

std::string crc32(const std::string &content) {
}

std::string deflate(const std::string &content) {
}

std::string gzip_compress(const std::string &content) {
    const std::string MAGIC = "\x1F\x8B";
    const std::string COMPRESSION_METHOD = "\x08";
    const std::string TIMESTAMP = "\x00\x00\x00\x00";
    std::string res = MAGIC + COMPRESSION_METHOD;
    return res;
}
