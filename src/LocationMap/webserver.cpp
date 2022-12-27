#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <vector>
#include <unistd.h>

#include "WebServer.h"
#include "Gzip.h"

void server_thread(std::function<std::string()> get_content, CompressionMethod compression_method) {
    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(6789);
    socket_address.sin_addr.s_addr = INADDR_ANY;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        std::cerr << "Failed to open socket\n";
    }

    constexpr int one = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) < 0) {
        std::cerr << "Failed to setsockopt(SO_REUSEADDR)\n";
    }

    if (bind(socket_fd, reinterpret_cast<struct sockaddr *>(&socket_address), sizeof(socket_address)) < 0) {
        std::cerr << "Failed to bind\n";
    }

    listen(socket_fd, 5);
    struct sockaddr_in client_address;
    socklen_t len = sizeof(client_address);
    while (true) {
        int new_fd = accept(socket_fd, reinterpret_cast<struct sockaddr *>(&client_address), &len);

        if (new_fd < 0) {
            std::cerr << "Failed to accept\n";
        }

        char buffer[1025];

        int n = read(new_fd, &buffer, 1024);
        if (n < 0) {
            std::cerr << "Failed to read\n";
        }

        std::vector<std::string> headers = {"HTTP/1.0 200 OK"};
        std::string payload;

        switch(compression_method) {
        case CompressionMethod::NO_COMPRESSION: {
            payload = get_content();
            break;
        }
        case CompressionMethod::DEFALTE: {
            headers.push_back("Content-Encoding: deflate");
            payload = deflate(get_content());
            break;
        }
        case CompressionMethod::GZIP: {
            headers.push_back("Content-Encoding: gzip");
            payload = gzip_compress(get_content());
            break;
        }
        default: {
            std::cerr << "Unsupported compression method\n";
            payload = get_content();
        }
        }

        std::string reply;

        for (auto header: headers) {
            reply += header + "\n";
        }

        reply += "\n" + payload;

        n = write(new_fd, reply.c_str(), reply.size());
        if (n < 0) {
            std::cerr << "Failed to write\n";
        }

        close(new_fd);
    }
    close(socket_fd);
}
