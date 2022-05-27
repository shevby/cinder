#include <memory>

#include "../MapGenerator.h"

namespace Cinder {

struct MapViewer {
    // TODO: replace MapGenerator with an actual map when I gets its proper class
    MapViewer(std::shared_ptr<Map> _map);

    int x; // top-left corner
    int y; // top-left corner
    void draw();

private:
    std::shared_ptr<Map> map;
};

} // namespace Cinder
