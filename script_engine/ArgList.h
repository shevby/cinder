#pragma once

#include <string>
#include <vector>

class ArgList {
public:
    ArgList();
    ArgList(const std::vector<std::string> &_args);
    std::string operator[](int index);
private:
    std::vector<std::string> args;
};
