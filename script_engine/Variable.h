#include <string>

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

} // namespace cinder
