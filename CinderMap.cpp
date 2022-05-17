#include "CinderMap.h"



CinderMap::CinderMap(sf::RenderWindow &w, std::vector<sf::Texture> &t) : Item{w}
{

}

CinderMap::CinderMap(sf::RenderWindow &w, std::vector<sf::Texture> &t, std::string path) : CinderMap{w, t}
{

    struct _Map {
        Cinder::MapTypes mapType;
        uint32_t width;
        uint32_t height;
        uint8_t map;
    };

    std::vector<sf::Image> tileImages;
    std::vector<sf::Image> tileRiverImages;

    for(int i = 0; i < _resources->textures().size(); i++) {
        tileImages.push_back(_resources->textures()[i].copyToImage());
    }

    for(int i = 0; i < _resources->riverTextures().size(); i++) {
        tileRiverImages.push_back(_resources->riverTextures()[i].copyToImage());
    }
    
    _filePath = path;

    std::ifstream input{_filePath, std::ios::binary};
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(input), {});

    Cinder::Map * mapStruct = (Cinder::Map*)&buffer[0];

    mapType = mapStruct->mapType;
    width = mapStruct->width;
    height = mapStruct->height;

    _map.width = width;
    _map.height = height;
    _map.mapType = mapType;

    Cinder::BiomeCell * mapData = (Cinder::BiomeCell*)&mapStruct->map;

    sf::Image img{};
    img.create(_map.width * TILE_WIDTH, _map.height * TILE_HEIGHT);


    _map.map.resize(_map.height);

    for(auto & m : _map.map) {
        m.resize(_map.width);
    }

    for(int tileIndex = 0; tileIndex < _map.height * _map.width; tileIndex++) {
        uint32_t yCoord = tileIndex / _map.width;
        uint32_t xCoord = tileIndex - (yCoord * _map.width);

        _map.map[yCoord][xCoord] = *reinterpret_cast<Cinder::BiomeCell*>(&mapData[tileIndex]);

        int tileY = 0;
        int tileX = 0;

        for(int y = yCoord * TILE_HEIGHT; y < yCoord * TILE_HEIGHT + TILE_HEIGHT; y++) {
            for(int x = xCoord * TILE_WIDTH; x < xCoord * TILE_WIDTH + TILE_WIDTH; x++) {

                img.setPixel(x, y, tileImages[_map.map[yCoord][xCoord].tile].getPixel(tileX, tileY));

                if(_map.map[yCoord][xCoord].river != static_cast<uint8_t>(Cinder::RiverDirection::NO_RIVER)) {
                    
                    auto pixel = tileRiverImages[_map.map[yCoord][xCoord].river].getPixel(tileX, tileY);

                    if(pixel.a > 0) { //Draw only if alpha more than 0
                        img.setPixel(x, y, tileRiverImages[_map.map[yCoord][xCoord].river].getPixel(tileX, tileY));
                    }

                }

                tileX++;
            }
            tileY++;
            tileX = 0;
        }
    }


    _texture.loadFromImage(img);

    _mapRect = sf::RectangleShape{sf::Vector2f(_map.width * TILE_WIDTH, _map.height * TILE_HEIGHT)};
    _mapRect.setTexture(&_texture);

}

int CinderMap::toPng()
{
    sf::Image img = _texture.copyToImage();

    std::cout << "\nConverting " << _filePath << " to PNG. Output file: " << _filePath << ".png ..." << std::endl;

    auto ret = img.saveToFile(_filePath + ".png");

    if(ret) {
        std::cout << "Done" << std::endl;
    }
    else {
        std::cout << "Failed!" << std::endl;
    }


    return ret ? 0 : 1;
}

CinderMap::~CinderMap()
{

}

void CinderMap::render()
{
    window.draw(_mapRect);
}

SaveMap CinderMap::saveBiom()
{
    SaveMap saveMap;

    saveMap.width = _map.width;
    saveMap.height = _map.height;

    saveMap.x = 0;
    saveMap.y = 0;

    saveMap.complex = true;

    saveMap.complexMap = _map.map;

    return saveMap;
}


