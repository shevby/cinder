#include <iostream>

#include "ArgList.h"

ArgList::ArgList() {}

ArgList::ArgList(const std::vector<std::string> &_args)
    : args(_args) {};

std::string ArgList::operator[](int index) {
    if ((index < 0) || (index >= args.size())) {
        std::cerr << "Index " << index << " is out of bounds (max index = " << args.size() - 1 << std::endl;
        return {};
    }
    return args[index];
}
