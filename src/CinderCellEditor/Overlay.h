#ifndef OVERLAY_H
#define OVERLAY_H

#include "Cursor.h"

/*!
 * \brief The Overlay class
 * represents the overlays which will be composed to the output map in EDIT mode
 */
class Overlay : public Item
{
    uint8_t currentTexture{0};
    sf::Vector2f pos;
    sf::Vector2f size{TILE_WIDTH, TILE_HEIGHT};
    sf::RectangleShape rectangle;

public:
    Overlay(sf::RenderWindow &w, std::vector<sf::Texture> &t);
    Overlay(Cursor & c);
    virtual void render() override;
    virtual SaveMap saveBiom() override;
};

#endif // OVERLAY_H
