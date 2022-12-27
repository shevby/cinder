#include <string>

/**
 * @brief Calculate Adler-32 checksum
 *
 * This checksum is used by gzip compression
 *
 * @return Adler-32 checksum stored as string
 */
std::string adler_32_checksum(const std::string &content);

/**
 * @brief Compress with DEFLATE algorithm and return only payload part
 */
std::string deflate_payload(const std::string &content);

/**
 * @brief Compress with DEFLATE algorithm
 */
std::string deflate(const std::string &content);

/**
 * @brief calculate CRC-32 sum used by Gzip
 */
std::string crc32(const std::string &content);

/**
 * @brief Compress payload in gzip-compartible format
 */
std::string gzip_compress(const std::string &content);
