#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadModel(std::filesystem::path rootPath)
{

  if (fs::exists(rootPath) && fs::isDirectory(rootPath))
  {
    auto dir = fs::ls(rootPath);

    for (auto p : dir)
    {
      if (fs::isDirectory(p))
      {
        _model[p.filename()] = this->_addType(p);
      }
    }
  }
  
}

Sin ResourceManager::_addType(std::filesystem::path path)
{
  Sin namespaces = Sin::Object();
  auto dir = fs::ls(path);

  for (auto p : dir)
  {
    if (fs::isDirectory(p))
    {
      namespaces[p.filename()] = this->_addNamespace(p);
    }
  }

  return namespaces;
}

Sin ResourceManager::_addNamespace(std::filesystem::path path)
{
  Sin resources = Sin::Object();
  auto dir = fs::ls(path);

  for (auto p : dir)
  {
    if (!fs::isDirectory(p))
    {
      resources[p.filename()] = std::string(p);
    }
  }

  return resources;
}

Sin &ResourceManager::getModel()
{
  return this->_model;
}