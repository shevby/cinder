#include <string>
#include <vector>

struct HttpRequest {
    HttpRequest(char *raw_request, size_t size);

    std::string first_line;
    std::vector<std::string> headers;
    std::string body;
};
