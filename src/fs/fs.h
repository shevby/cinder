
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs
{
  bool exists(const std::filesystem::path filePath);
  std::filesystem::path cwd();
  std::filesystem::path join(const std::filesystem::path filePath);
  std::string readAll(const std::filesystem::path filePath);
  std::vector<char> readAllBytes(const std::filesystem::path filePath);
};