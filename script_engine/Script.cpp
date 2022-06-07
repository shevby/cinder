#include <iostream>
#include <sstream>
#include <unordered_map>

#include "Script.h"
#include "Variable.h"

namespace cinder {

VariableStorage vars;

SingleScriptLine::SingleScriptLine(const std::vector<std::string> &words) {
    if (words.size() == 0) {
        std::cerr << "Command not provided\n";
    }

    cmd = words[0];

    std::vector<std::string> _args;
    for (size_t i = 1; i<words.size(); ++i) {
        _args.push_back(words[i]);
    }

    args = _args;
}

static std::string deref_value(const std::string &name) {
    return (name.size() > 0) && (name[0] == '$')
         ? vars[name]->read()
         : name;
}

static int get_int(const std::string &value) {
    try {
        return std::stoi(deref_value(value));
    }
    catch (const std::exception& ex) {
        std::cerr << "Can't convert '" << value << "' to integer: " << ex.what() << "\n";
        return 0;
    }
}

void SingleScript::execute() {
    running = false;
    for (const auto line : lines) {
        auto cmd = line.cmd;
        auto args = line.args;
        if (cmd == "SET") {
            vars[args[0]]->write(deref_value(args[1]));
        }
        else if (cmd == "RETURN_IF") {
            std::string op = args[0];
            int x = get_int(args[1]);
            int y = get_int(args[2]);
            if (op == "MORE") {
                if (x > y) return;
            } else if (op == "LESS") {
                if (x < y) return;
            }
        }
        else if (cmd == "ADD") {
            int new_value = get_int("$" + args[0]) + get_int(args[1]);
            vars[args[0]]->write(std::to_string(new_value));
        }
        else if (cmd == "PRINT") {
            std::cout << deref_value(args[0]) << "\n";
        }
        else if (cmd == "REPEAT") {
            running = true;
        }
    }
}

Script::Script(const std::string &script) {
    std::stringstream ss(script);
    std::string line;

    SingleScript current_script;

    while (std::getline(ss, line)) {
        std::stringstream ss2(line);

        std::vector<std::string> words;
        while (ss2.good()) {
            std::string word;
            ss2 >> word;
            words.push_back(word);
        }

        if (words[0] == "SCRIPT") {
            scripts.push_back(current_script);
            current_script = {};
        }

        current_script.lines.push_back(SingleScriptLine(words));
    }

    scripts.push_back(current_script);
}

void Script::execute_step() {
    for (auto& script : scripts) {
        if (script.running) {
            script.execute();
        }
    }
}

} // namespace cinder
