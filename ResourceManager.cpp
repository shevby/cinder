#include "ResourceManager.h"

std::shared_ptr<ResourceManager> ResourceManager::_self = nullptr;

ResourceManager::ResourceManager()
{
    for(auto & texturePath : TEXTURE_PATHS) {
        _textures.push_back(sf::Texture{});
        _textures[_textures.size() - 1].loadFromFile(texturePath);
        _textures[_textures.size() - 1].setRepeated(true);
    }

    for(auto & texturePath : RIVER_TEXTURE_PATHS) {
        _riverTextures.push_back(sf::Texture{});
        _riverTextures[_riverTextures.size() - 1].loadFromFile(texturePath);
        _riverTextures[_riverTextures.size() - 1].setRepeated(true);
    }
}

const std::vector<sf::Texture> &ResourceManager::riverTextures() const
{
    return _riverTextures;
}

const std::vector<sf::Texture> &ResourceManager::textures() const
{
    return _textures;
}


std::shared_ptr<ResourceManager> ResourceManager::getInstance()
{
    if(_self.get() == nullptr) {
        ResourceManager * manager = new ResourceManager();
        _self = std::shared_ptr<ResourceManager>{manager};
    }

    return _self;
}
