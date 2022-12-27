#include <functional>
#include <string>

enum class CompressionMethod {
    NO_COMPRESSION,
    DEFALTE,
    GZIP,
};

/**
 * @brief Start crude HTTP-server that can only output data to users
 *
 * @param get_content method that creates content to be distributed
 * @param compression_method HTTP compression to be used
 */
void server_thread(std::function<std::string()> get_content,
                   CompressionMethod compression_method = CompressionMethod::NO_COMPRESSION);
