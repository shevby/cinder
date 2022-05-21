#include <sstream>
#include <string>
#include <vector>

namespace cinder {

struct SingleScriptLine {
    SingleScriptLine(const std::vector<std::string> &words);
    std::string cmd;
    std::vector<std::string> args;
};

struct SingleScript {
    std::vector<SingleScriptLine> lines;
    void execute();
    bool running = true;
};

class Script {
public:
    Script(const std::string &script);
    std::vector<SingleScript> scripts;
    void execute_step();
};

} // namespace cinder
