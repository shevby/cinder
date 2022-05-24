#include "../MapGenerator.h"

namespace Cinder {

struct MapViewer {
    // TODO: replace MapGenerator with an actual map when I gets its proper class
    MapViewer(MapGenerator _map);

    int x; // top-left corner
    int y; // top-left corner
    void draw();

private:
    MapGenerator map;
};

} // namespace Cinder
