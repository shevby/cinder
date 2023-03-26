#pragma once

#include <iostream>

#include "fs.h"
#include "sin.h"

class ResourceManager
{
public:
  ResourceManager();
  virtual ~ResourceManager();

  void loadModel(std::filesystem::path rootPath);
  Sin &getModel();

private:
  Sin _addType(std::filesystem::path path);
  Sin _addNamespace(std::filesystem::path path);

  Sin _model;
};