#include <string>
#include <vector>
#include <unordered_map>

#include "Variable.h"

namespace cinder {

void Variable::write(const std::string &new_value) {
    value = new_value;
}

std::string Variable::read() {
    return value;
}

std::unordered_map<std::string, void*> variables;

} // namespace cinder
