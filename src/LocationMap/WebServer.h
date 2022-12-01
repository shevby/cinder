#include <functional>
#include <string>

void server_thread(std::function<std::string()> get_content);
