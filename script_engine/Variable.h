#include <memory>
#include <string>
#include <unordered_map>

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

class VariableStorage {
public:
    GenericVariable* operator[](const std::string &name);
private:
    using _map = std::unordered_map<std::string, void*>;
    std::shared_ptr<_map> vars = std::make_shared<_map>();
};

} // namespace cinder
