#pragma once

#include <functional>

#include "Item.h"

class Cursor : public Item
{
    uint8_t _currentTexture{0};
    sf::Vector2f _startPos{-1, -1};
    sf::Vector2f _pos;
    sf::Vector2f _size{TILE_WIDTH, TILE_HEIGHT};
    sf::RectangleShape _rectangle;
    std::vector<sf::Texture> _cursorTextures;
    std::function<void()> _onDrawAreaSelectedCallback{nullptr};


public:
    Cursor(sf::RenderWindow &w);
    /*!
     * \brief render
     * Renders the cursor
     */
    virtual void render();
    /*!
     * \brief handleMouse
     * Handles mouse events
     * \param event
     */
    void handleMouse(MouseEvent event);
    /*!
     * \brief reset
     * Resets the state of the cursor
     */
    void reset();

    //Getters
    const sf::Vector2f &getPos() const;
    const sf::Vector2f &getSize() const;
    uint8_t getCurrentTexture() const;
    uint32_t mapWidth;
    uint32_t mapHeight;

    /*!
     * \brief onDrawAreaSelected
     * Subscribe to DrawAreaSelected event.
     * \param callback
     * Will be called when the user selects the area do draw with some tile
     */
    void onDrawAreaSelected(std::function<void()> callback);
    void setCurrentTexture(uint8_t newCurrentTexture);
    virtual SaveMap saveBiom();
};
