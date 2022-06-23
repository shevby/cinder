#ifndef CINDERMAP_H
#define CINDERMAP_H

#include <iostream>
#include <fstream>

#include "Item.h"
#include "constants.h"

/*!
 * \brief The CinderMap class
 * represents the opened map
 */
class CinderMap: public Item {
    std::string _filePath;
    sf::Texture _texture;
    sf::RectangleShape _mapRect;
    Cinder::Map _map;
public:
    Cinder::MapTypes mapType;
    uint32_t width;
    uint32_t height;

    CinderMap(sf::RenderWindow & w, std::vector<sf::Texture> & t);
    CinderMap(sf::RenderWindow & w, std::vector<sf::Texture> & t, std::string path);
    virtual ~CinderMap();
    /*!
     * \brief toPng
     * transforms raw map to PNG and saves it with name [filePath].png
     * \return
     */
    int toPng();
    /*!
     * \brief render
     * renders map in the main window
     */
    virtual void render();
    virtual SaveMap saveBiom();

};

#endif // CINDERMAP_H
