#pragma once

#include <vector>

#include "map.h"

namespace Cinder {

std::vector<std::vector<Biomes>> generate_bioms_perlin_noise(uint64_t seed, size_t width, size_t height);

}; // namespace Cinder
