#include <cstdint>

namespace Cinder {

class Random {
public:
    // do not use -1 as seed otherwise all the returned values will be unit64_t(-1)
    Random(uint64_t seed);
    Random() = delete;

    uint64_t rand();
private:
    void shift();
    uint64_t state;
};

}; // namespace Cinder
