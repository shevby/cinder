#include "fs.h"

bool fs::exists(const std::filesystem::path filePath)
{
  return std::filesystem::exists(filePath);
}

std::filesystem::path fs::cwd()
{
  return std::filesystem::current_path();
}

std::filesystem::path fs::join(const std::filesystem::path filePath)
{
  return std::filesystem::absolute(filePath);
}

std::string fs::readAll(const std::filesystem::path filePath)
{
  std::ifstream file(filePath);
  if (!file.is_open())
  {
    std::cerr << "Can't open the file - '"
              << filePath << "'" << std::endl;
    exit(EXIT_FAILURE);
  }
  return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

std::vector<char> fs::readAllBytes(const std::filesystem::path filePath)
{
  std::ifstream file(filePath, std::ios::binary | std::ios::ate);
  std::vector<char> result;

  file.seekg(0, std::ios::end);
  size_t length = file.tellg();
  file.seekg(0, std::ios::beg);

  result.reserve(length);

  file.read(&result[0], length);

  return result;
}
