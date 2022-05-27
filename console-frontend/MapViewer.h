#include <memory>

#include "../MapGenerator.h"

namespace Cinder {

struct MapViewer {
    MapViewer(std::shared_ptr<Map> _map);
    static void initColors();

    int x; // top-left corner
    int y; // top-left corner
    void draw();

private:
    std::shared_ptr<Map> map;
};

} // namespace Cinder
