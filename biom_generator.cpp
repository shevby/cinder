#include <vector>
#include <stdlib.h>

#define BIOM_DEMO // TODO: remove in production

#ifdef BIOM_DEMO
#include <iostream>
#include <cstring>
#endif

/**
 * @brief basic biom generator
 *
 * This method randomly distributes biom centers over the map
 * Each tile obtains the type of the closest biom center
 */
template <typename TILE_TYPE>
std::vector<std::vector<TILE_TYPE>> generate_bioms(unsigned int seed, size_t width, size_t height, std::vector<TILE_TYPE> bioms)
{
    srand(seed);

    struct biom_center_t {
        int x;
        int y;
        TILE_TYPE tile;
        biom_center_t(int _x, int _y, int _tile): x(_x), y(_y), tile(_tile) {};
    };

    std::vector<biom_center_t> biom_centers;
    for (auto biom : bioms) {
        biom_centers.push_back(biom_center_t(rand() % width, rand() % height, biom));
    }

    std::vector<std::vector<TILE_TYPE>> map;

    for (size_t x = 0; x < width; ++x) {
        std::vector<TILE_TYPE> row;
        for (size_t y = 0; y < height; ++y) {
            TILE_TYPE closest_biom = bioms[0];
            double min_distance = 90000000000000000000000000.0; // a big number
            for (auto biom_center : biom_centers) {
                auto x_diff = std::abs((double)(x - biom_center.x));
                auto y_diff = std::abs((double)(y - biom_center.y));
                double distance = x_diff * x_diff + y_diff * y_diff;
                if (distance < min_distance) {
                    min_distance = distance;
                    closest_biom = biom_center.tile;
                }
            }
            row.push_back(closest_biom);
        }
        map.push_back(row);
    }
    return map;
}

#ifdef BIOM_DEMO

static void write_vector(FILE *f, const std::vector<unsigned char> &vec) {
    fwrite(&vec[0], sizeof(unsigned char), vec.size(), f);
}

static void write_uint32(FILE *f, uint32_t value) {
    write_vector(f, {
        static_cast<unsigned char>(value & 0xFF),
        static_cast<unsigned char>((value >> 8) & 0xFF),
        static_cast<unsigned char>((value >> 16) & 0xFF),
        static_cast<unsigned char>((value >> 24) & 0xFF)
    });
}

static uint32_t tile_to_bmppixel(unsigned char ch) {
    switch(ch) {
    case '.': return 0xFF000000;
    case 'X': return 0xFFFFFFFF;
    case '^': return 0xFFFF0000;
    case '#': return 0xFF00FF00;
    case '|': return 0xFF0000FF;
    default: return 0xFF808080;
    }
}

int main() {
    const char *biom_string = "............................................................................"
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
    "######################################################################################################"
    "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    std::vector<char> bioms;
    for (size_t i = 0; i < strlen(biom_string); ++i) {
        bioms.push_back(biom_string[i]);
    }

    auto map = generate_bioms<char>(time(NULL), 1024, 1024, bioms);
    // command-line map output
    /*
    for (const auto &row : map) {
        for (const auto tile : row) {
            std::cout << tile;
        }
        std::cout << "\n";
    }
    */

    // store to a *.bmp file
    FILE *f = fopen("map.bmp", "wb");
    constexpr uint32_t bmp_header_size = 14;
    uint32_t dip_header_size = 108;
    uint32_t bmp_data_size = 4 * map.size() * map[0].size();

    // BMP header
    write_vector(f, {'B', 'M'}); // ID field
    write_uint32(f, bmp_header_size + dip_header_size + bmp_data_size); // total size
    write_vector(f, {0, 0, 0, 0}); // Unused
    write_uint32(f, bmp_header_size + dip_header_size); // start of bmp data (pixel array)

    // DIB header
    write_uint32(f, dip_header_size);
    write_uint32(f, map[0].size()); // Width of the bitmap in pixels
    write_uint32(f, map.size()); // Height of the bitmap in pixels
    write_vector(f, {0x01, 0x00}); // Number of color planes being used
    write_vector(f, {0x20, 0x00}); // Number of bits per pixel
    write_uint32(f, 3); // BI_BITFIELDS, no pixel array compression used
    write_uint32(f, bmp_data_size); // Size of the raw bitmap data
    write_vector(f, {0x13, 0x0B, 0x00, 0x00, 0x13, 0x0B, 0x00, 0x00}); // Print resolution of the image
    write_uint32(f, 0); // Number of colors in the palette
    write_uint32(f, 0); // All colors are important
    write_uint32(f, 0x00FF0000); // Red channel bit mask // TODO: check endianness
    write_uint32(f, 0x0000FF00); // Green channel bit mask // TODO: check endianness
    write_uint32(f, 0x000000FF); // Blue channel bit mask // TODO: check endianness
    write_uint32(f, 0xFF000000); // Alpha channel bit mask // TODO: check endianness
    write_vector(f, {0x20, 0x6E, 0x69, 0x57}); // little-endian "Win " // LCS_WINDOWS_COLOR_SPACE
    for (size_t i=0; 4*i<0x24; ++i) {
        write_uint32(f, 0); // CIEXYZTRIPLE Color Space endpoints
    }
    write_uint32(f, 0); // Red gamma
    write_uint32(f, 0); // Green gamma
    write_uint32(f, 0); // Blue gamma

    // Bitmap data
    for (const auto &row : map) {
        for (const auto tile : row) {
            write_uint32(f, tile_to_bmppixel(tile));
        }
    }
}
#endif
