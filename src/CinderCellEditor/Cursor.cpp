#include "Cursor.h"

sf::Texture toCursorTexture(sf::Texture & t) {
    sf::Image img = t.copyToImage();
    auto xLen = img.getSize().x;
    auto yLen = img.getSize().y;

    for(int y = 0; y < yLen; y++) {
        for(int x = 0; x < xLen; x++) {

            if(x - 1 < 0 || x + 2 > xLen || y - 1 < 0 || y + 2 > yLen) {
                img.setPixel(x, y, sf::Color::Red);
            }

        }
    }

    sf::Texture texture;

    texture.loadFromImage(img);

    texture.setRepeated(true);

    return texture;
}

const sf::Vector2f &Cursor::getPos() const
{
    return _pos;
}

const sf::Vector2f &Cursor::getSize() const
{
    return _size;
}

uint8_t Cursor::getCurrentTexture() const
{
    return _currentTexture;
}

void Cursor::onDrawAreaSelected(std::function<void ()> callback)
{
    _onDrawAreaSelectedCallback = callback;
}

void Cursor::setCurrentTexture(uint8_t newCurrentTexture)
{
    _currentTexture = newCurrentTexture;
}

SaveMap Cursor::saveBiom()
{
    return SaveMap{};
}

Cursor::Cursor(sf::RenderWindow &w) : Item{w}
{
    for(auto texture : _resources->textures()) {
        _cursorTextures.push_back(toCursorTexture(texture));
    }


}


void Cursor::handleMouse(MouseEvent event)
{
    auto position = window.mapPixelToCoords(event.pos);
    position.x = static_cast<int>(position.x - static_cast<int>(position.x) % TILE_WIDTH);
    position.y = static_cast<int>(position.y - static_cast<int>(position.y) % TILE_HEIGHT);

    if(position.x < 0) position.x = 0;
    if(position.y < 0) position.y = 0;
    if(position.x > mapWidth * TILE_WIDTH) position.x = mapWidth * TILE_WIDTH - TILE_WIDTH;
    if(position.y > mapHeight * TILE_HEIGHT) position.y = mapHeight * TILE_HEIGHT - TILE_HEIGHT;

    if(event.left && _startPos.x >= 0 && _startPos.y >= 0) {
        if(_onDrawAreaSelectedCallback != nullptr) {
            _onDrawAreaSelectedCallback();
        }
        reset();
        return;
    }

    if(_startPos.x >= 0 && _startPos.y >=0) {
        _size = (position - _startPos);
        _size += sf::Vector2f{ static_cast<float>(_size.x >= 0 ? TILE_WIDTH: 0), static_cast<float>(_size.y >= 0 ? TILE_HEIGHT : 0)};
    }
    else {
        _pos = position;
    }

    if(event.left) {
        _startPos = position;
    } else if (event.right) {
        reset();
    }


}

void Cursor::reset()
{
    _startPos = {-1, -1};
    _size = {TILE_WIDTH, TILE_HEIGHT};
}

void Cursor::render()
{
    _rectangle.setPosition(_pos);
    _rectangle.setSize(_size);
    _rectangle.setTexture(&_cursorTextures[_currentTexture]);
    _rectangle.setTextureRect({0, 0, static_cast<int>(_size.x), static_cast<int>(_size.y)});


    window.draw(_rectangle);
}

