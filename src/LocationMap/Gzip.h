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
 * @brief Compress payload in gzip-compartible format
 */
std::string gzip_compress(const std::string &content);
