#include <string>
#include <vector>

struct JsonConfig {
    std::string tab = "    ";
    std::string newline = "\n";
};

class JsonSerializer {
public:
    JsonSerializer(JsonConfig config);
    void add(const std::string &key, const std::string &value);
    void add(const std::string &key, int64_t value);
    void add(const std::string &key, std::vector<std::string> lines_to_add);
    void add_to_array(std::vector<std::string> lines_to_add);
    std::vector<std::string> get_json_lines(bool is_array = false);
    std::string get_json(bool is_array = false);
private:
    JsonConfig config;
    std::vector<std::string> lines;
};
