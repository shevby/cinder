#pragma once
#include "fs.h"

class Loader
{
private:
  /* data */
public:
  Loader(/* args */);
  ~Loader();

  static std::string detectType(std::filesystem::path filePath);
};

