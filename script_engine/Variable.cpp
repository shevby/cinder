#include <string>
#include <vector>

#include "Variable.h"

namespace cinder {

void Variable::write(const std::string &new_value) {
    value = new_value;
}

std::string Variable::read() {
    return value;
}

GenericVariable* VariableStorage::operator[](const std::string &name) {
    auto it = vars->find(name);
    if (it == vars->end()) {
        auto var = new Variable();
        vars->insert({name, var});
        return var;
    }
    else {
        return (GenericVariable *)it->second;
    }
}

} // namespace cinder
