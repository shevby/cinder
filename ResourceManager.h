#pragma once 

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

const std::vector<std::string> TEXTURE_PATHS = {
    "resources/textures/biomes/water.png",
    "resources/textures/biomes/field.png",
    "resources/textures/biomes/forest.png",
    "resources/textures/biomes/rock.png",
    "resources/textures/biomes/highrock.png",
    "resources/textures/biomes/glacier.png",
    "resources/textures/biomes/swamp.png",
    "resources/textures/biomes/desert.png",
    "resources/textures/biomes/savanna.png"
};


const std::vector<std::string> RIVER_TEXTURE_PATHS = {
    "resources/textures/biomes/river_topDown.png",
    "resources/textures/biomes/river_topLeft.png",
    "resources/textures/biomes/river_topRight.png",
    "resources/textures/biomes/river_leftRight.png",
    "resources/textures/biomes/river_downRight.png",
    "resources/textures/biomes/river_downLeft.png"
};



class ResourceManager
{
protected:
    ResourceManager();
    static std::shared_ptr<ResourceManager> _self;
    std::vector<sf::Texture> _textures;
    std::vector<sf::Texture> _riverTextures;

public:
    void operator=(const ResourceManager &) = delete;

    static std::shared_ptr<ResourceManager> getInstance();
    const std::vector<sf::Texture> &textures() const;
    const std::vector<sf::Texture> &riverTextures() const;
};

