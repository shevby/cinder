#include "File.h"

namespace fs
{

  bool exists(const path filePath);
  path cwd();
  path join(const path filePath);
  std::string readAll(const path filePath);
  std::vector<char> readAllBytes(const path filePath);
  File open(path filePath, std::string mode);
  uintmax_t size(const path filePath);
  std::vector<path> readDir(path dirPath = ".");
  std::vector<path> ls(path dirPath = ".");
  std::vector<path> dir(path dirPath = ".");

  std::vector<path> readDirRecursive(path dirPath = ".");
  std::vector<path> lsr(path dirPath = ".");
  std::vector<path> dirr(path dirPath = ".");


  bool walk(path dirPath, std::function<bool(const std::filesystem::directory_entry&)> callback);
  bool walkRecursive(path dirPath, std::function<bool(const std::filesystem::directory_entry&)> callback);
  bool walkr(path dirPath, std::function<bool(const std::filesystem::directory_entry&)> callback);
};