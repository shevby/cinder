#include <string>
#include <unordered_map>

struct arg_parser {
    std::string cmd;
    std::unordered_map<std::string, std::string> params;

    /**
     * Initialize arg_parser struct from the argc/argv pair
     */
    arg_parser(int argc, char **argv);

    /**
     * Print parsed parameters.
     */
    void debug_print();
};
