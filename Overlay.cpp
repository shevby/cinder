#include "Overlay.h"

Overlay::Overlay(sf::RenderWindow &w, std::vector<sf::Texture> &t) : Item{w}
{

}

Overlay::Overlay(Cursor &c) : Item{c}
{
    pos = c.getPos();
    size = c.getSize();
    currentTexture = c.getCurrentTexture();


    rectangle.setPosition(pos);
    rectangle.setSize(size);
    rectangle.setTexture(&_resources->textures()[currentTexture]);
    rectangle.setTextureRect({0, 0, static_cast<int>(size.x), static_cast<int>(size.y)});
}

void Overlay::render()
{
    window.draw(rectangle);
}

SaveMap Overlay::saveBiom()
{
    SaveMap saveMap;

    saveMap.complex = false;
    saveMap.tile.tile = (uint8_t)this->currentTexture;

    saveMap.x = pos.x / TILE_WIDTH;
    saveMap.y = pos.y / TILE_HEIGHT;

    saveMap.width = size.x / TILE_WIDTH;
    saveMap.height = size.y / TILE_HEIGHT;

    if((size.x / TILE_WIDTH) < 0) {
        saveMap.x = saveMap.x + (size.x / TILE_WIDTH);
        saveMap.width = size.x / -TILE_WIDTH;
    }

    if((size.y / TILE_HEIGHT) < 0) {
        saveMap.y = saveMap.y + (size.y / TILE_WIDTH);
        saveMap.height = size.y / -TILE_WIDTH;
    }

    return saveMap;

}
