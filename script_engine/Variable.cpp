#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

namespace cinder {

/**
 * A generic readable/writable entity
 */
class GenericVariable {
public:
    virtual void write(const std::string &new_value) = 0;
    virtual std::string read() = 0;
};

class Variable: public GenericVariable {
public:
    void write(const std::string &new_value) override;
    std::string read() override;
private:
    std::string value;
};

void Variable::write(const std::string &new_value) {
    value = new_value;
}

std::string Variable::read() {
    return value;
}

std::map<std::string, *GenericVariable> variables;

struct SingleScriptLine {
    SingleScriptLine(const std::string &line);
    void execute();
};

SingleScriptLine::SingleScriptLine(const std::string &line) {

}

SingleScriptLine::execute() {

}

struct SingleScript {
    std::vector<SingleScriptLine> lines;
};

class Script {
public:
    Script(const std::string &script);
};

Script::Script(const std::string &script) {
    std::stringstream ss(script);
    typedef std::vector<std::vector<std::string>> single_script_t;
    single_script_t s;
    std::string line;

    std::vector<single_script_t> scripts;
    single_script_t current_script;

    while (std::getline(ss, line)) {
        std::cout << "Line: " << line << "\n";
        std::stringstream ss2(line);

        std::vector<std::string> words;
        while (ss2.good()) {
            std::string word;
            ss2 >> word;
            std::cout << word << "\n";
            words.push_back(word);
        }

        if (words[0] == "SCRIPT") {
            scripts.push_back(current_script);
        }

        current_script.push_back(words);
    }

    scripts.push_back(current_script);

    while (true) {
        for (const auto script : scripts) {
            for (const auto line : script) {
                std::cout << line[0] << "\n";
                std::string cmd = line[0];
                std::vector<std::string> args = line;
                args.erase(args.begin());
            }
        }
    }
};

} // namespace cinder

int main() {
    std::string script_text =
    "SCRIPT\n"
    "    ASSIGN_VALUE A 1\n"
    "    ASSIGN_VALUE B 1\n"
    "    ASSIGN_VALUE MAX_STEPS 20\n"
    "ENDSCRIPT\n"
    "\n"
    "SCRIPT\n"
    "    CONDITION MORE MAX_STEPS I\n"
    "    ASSIGN_VALUE ONE 1\n"
    "    ADD I ONE\n"
    "    ASSIGN_VARIABLE TMP A\n"
    "    ADD A B\n"
    "    ASSIGN_VARIABLE B TMP\n"
    "    REPEAT\n"
    "ENDSCRIPT\n";

    cinder::Script script(script_text);
}
