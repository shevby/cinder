#include <iostream>
#include <unordered_map>

#include "Script.h"
#include "Variable.h"

namespace cinder {

extern std::unordered_map<std::string, void*> variables;

SingleScriptLine::SingleScriptLine(const std::vector<std::string> &words) {
    if (words.size() == 0) {
        std::cerr << "Command not provided\n";
    }

    cmd = words[0];
    for (size_t i = 1; i<words.size(); ++i) {
        args.push_back(words[i]);
    }
}

static GenericVariable *get_var(const std::string &name) {
    auto it = variables.find(name);
    if (it == variables.end()) {
        auto var = new Variable();
        variables.insert({name, var});
        return var;
    }
    else {
        return (GenericVariable *)it->second;
    }
}

static int get_int(const std::string &name) {
    try {
        auto var = get_var(name);
        return std::stoi(var->read());
    }
    catch (const std::exception& ex) {
        std::cerr << "Can't read int of " << name << " " << ex.what() << "\n";
        return 0;
    }
}

void SingleScript::execute() {
    running = false;
    for (const auto line : lines) {
        auto cmd = line.cmd;
        auto args = line.args;
        if (cmd == "ASSIGN_VALUE") {
        	get_var(args[0])->write(args[1]);
        }
        else if (cmd == "ASSIGN_VARIABLE") {
            get_var(args[0])->write(get_var(args[1])->read());
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
            int new_value = get_int(args[0]) + get_int(args[1]);
            get_var(args[0])->write(std::to_string(new_value));
        }
        else if (cmd == "PRINT") {
            std::cout << get_var(args[0])->read() << "\n";
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
