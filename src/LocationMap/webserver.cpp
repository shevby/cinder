#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
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

        std::string reply = "HTTP/1.0 200 OK\n"
                            "\n"
                            "It works!\n";

        n = write(new_fd, reply.c_str(), reply.size());
        if (n < 0) {
            std::cerr << "Failed to write\n";
        }

        close(new_fd);
    }
    close(socket_fd);
}
