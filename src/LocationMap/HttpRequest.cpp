#include "HttpRequest.h"

#include <cstring>

HttpRequest::HttpRequest(char *raw_request, size_t size) {
    char *beginning = raw_request;

    // Stage 1: Read the first line of the request

    char *first_newline = strpbrk(raw_request, "\n");
    if (!first_newline) {
        first_line = raw_request;
        return;
    }

    *first_newline = '\0';
    first_line = raw_request;
    raw_request = first_newline + 1;

    // Stage 2: Read the headers

    while (raw_request) {
        char *next_newline = strpbrk(raw_request, "\n");
        if (!next_newline) {
            if (strlen(raw_request)) {
                headers.push_back(raw_request);
            }
            return;
        }

        *next_newline = '\0';

        if (!strlen(raw_request)) {
            raw_request = next_newline + 1;
            break;
        }

        headers.push_back(raw_request);
        raw_request = next_newline + 1;
    }

    // Stage 3: Read the request body

    size_t body_size = beginning + size - raw_request;
    body = std::string(raw_request, body_size);
}
