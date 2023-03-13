#include "Server.h"

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include <mutex>

Server::Server(int port) : port_(port), running_(true), data_("{}") {
    // Create a socket
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ == -1) {
        std::cerr << "Failed to create socket\n";
        running_ = false;
        return;
    }

    // Bind the socket to a port
    sockaddr_in address;
    std::memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);
    if (bind(server_fd_, (sockaddr *)&address, sizeof(address)) == -1) {
        std::cerr << "Failed to bind socket\n";
        close(server_fd_);
        server_fd_ = -1;
        running_ = false;
        return;
    }

    // Listen for incoming connections
    if (listen(server_fd_, 1) == -1) {
        std::cerr << "Failed to listen for connections\n";
        close(server_fd_);
        server_fd_ = -1;
        running_ = false;
        return;
    }

    std::cout << "Server started on port " << port_ << "\n";

    // Start a thread to accept connections
    accept_thread_ = std::thread(&Server::accept_connections, this);
}

Server::~Server() {
    running_ = false;
    close(server_fd_);

    if (accept_thread_.joinable()) {
        accept_thread_.join();
    }

    std::cout << "Server stopped\n";
}

void Server::update_data(const std::string& data) {
    std::lock_guard<std::mutex> lock(data_mutex_);
    data_ = data;

    for (int client_fd : client_fds_) {
        send_data(client_fd, data_);
    }
}

void Server::accept_connections() {
    while (running_) {
        int client_fd = accept(server_fd_, nullptr, nullptr);
        if (client_fd == -1) {
            std::cerr << "Failed to accept connection\n";
            continue;
        }

        // Add the client socket to the list of connected clients
        std::lock_guard<std::mutex> lock(client_fds_mutex_);
        client_fds_.push_back(client_fd);

        // Send data to the client
        send_data(client_fd, data_);
    }
}

void Server::send_data(int client_fd, const std::string& data) {
    int length = data.size();

    // Send length of data
    std::string length_str = std::to_string(length) + "\n";
    send(client_fd, length_str.c_str(), length_str.size(), 0);

    // Send data
    send(client_fd, data.c_str(), data.size(), 0);
}
