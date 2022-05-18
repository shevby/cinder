#include <string>
#include <unordered_map>

struct arg_parser {
    std::unordered_map<std::string, std::string> params;

    /**
     * Initialize arg_parser struct from the argc/argv pair
     */
    arg_parser(int argc, char **argv);
};
