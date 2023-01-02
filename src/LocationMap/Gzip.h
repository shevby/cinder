#include <string>
#include <vector>

struct lz77_entry {
    uint16_t offset;
    uint16_t size;
    char ch;

    lz77_entry(uint16_t _offset, uint16_t _size);
    lz77_entry(char _ch);

    auto operator<=>(const lz77_entry&) const = default;
};

struct lz77_max_length_match {
    size_t absolute_pos;
    size_t length;
};

lz77_max_length_match find_max_length_match(const std::string &content, size_t current_index, size_t starting_search_index);

/**
 * @param min_match_length Minimal accepted common sequence of bytes. The default value of 3 is chosen because for smaller values the overhead encoding the reference outweights the benefit.
 */
std::vector<lz77_entry> to_lz77_entries(const std::string &content, size_t search_distance, size_t min_match_length = 3);

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
