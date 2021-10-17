#include <sstream>
#include <string>
#include <vector>

namespace Cinder {

struct parsed_sin {
    std::string name;
    std::string _type;
    std::string value;
};

bool parse_sins(std::stringstream &ss, std::vector<parsed_sin> &sins);

void run_sin_parser_tests();

}; // namespace Cinder
