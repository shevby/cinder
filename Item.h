#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "constants.h"
#include "Controls.h"
#include "ResourceManager.h"

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;


struct SaveMap {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    Cinder::BiomeCell tile;
    bool complex = false;
    std::vector<std::vector<Cinder::BiomeCell>> complexMap;

    friend std::ostream& operator<<(std::ostream& os, const SaveMap& sm) {
        os << "x: " << sm.x << std::endl;
        os << "y: " << sm.y << std::endl;
        os << "width: " << sm.width << std::endl;
        os << "height: " << sm.height << std::endl;
        os << "tile: " << sm.tile << std::endl;
        os << "complex: " << (bool)sm.complex << std::endl;
        os << std::endl;

        return os;
    }
};

/*!
 * \brief The Item class
 * pure virtual, base for objects which will be rendered in the main loops
 */
class Item
{
protected:
    /*!
     * \brief window
     * Reference to the main application window
     */
    sf::RenderWindow & window;
    std::shared_ptr<ResourceManager> _resources;
    

public:
    Item(sf::RenderWindow & w) : window{w} {
        _resources = ResourceManager::getInstance();
    };
    virtual ~Item(){};
    virtual void render() = 0;
    virtual SaveMap saveBiom() = 0;
};



#endif // RENDERABLE_H
