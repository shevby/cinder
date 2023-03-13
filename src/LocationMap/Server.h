#ifndef LOCATION_MAP_SERVER_H
#define LOCATION_MAP_SERVER_H

#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Server {
public:
    Server(int port);
    ~Server();
    void update_data(const std::string& data);

private:
    void accept_connections();
    void send_data(int client_fd, const std::string& data);

    int port_;
    int server_fd_ = -1;
    bool running_;
    std::string data_;
    std::vector<int> client_fds_;
    std::thread accept_thread_;
    std::mutex client_fds_mutex_;
    std::mutex data_mutex_;
};

#endif // LOCATION_MAP_SERVER_H

