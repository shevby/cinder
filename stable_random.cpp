#include "stable_random.h"

namespace Cinder {

static inline uint64_t extract_bit(uint64_t num, int bit) {
    return (num >> bit) & 1;
}

Random::Random(uint64_t seed) {
    state = seed;
}

void Random::shift() {
    uint64_t next_bit = (1 + extract_bit(state, 63) + extract_bit(state, 62) + extract_bit(state, 60) + extract_bit(state, 59)) % 2;
    state = (state << 1) + next_bit;
}

uint64_t Random::rand() {
    for (std::size_t i = 0; i < 64; ++i) {
        shift();
    }
    return state;
}

}; // namespace Cinder
