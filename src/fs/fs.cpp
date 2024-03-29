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

  result.resize(length);

  file.read(&result[0], length);

  return result;
}

uintmax_t fs::size(const path filePath)
{
  return std::filesystem::file_size(filePath);
}

bool fs::walk(path dirPath, std::function<bool(const std::filesystem::directory_entry &)> callback)
{
  if (!fs::exists(dirPath))
  {
    std::cerr << "Directory '" << dirPath << "' doesn't exist!\n";
    exit(0);
  }

  for (auto &entry : std::filesystem::directory_iterator{dirPath})
  {
    auto interupt = callback(entry);

    if (interupt)
    {
      return true;
    }
  }

  return false;
}

bool fs::walkRecursive(path dirPath, std::function<bool(const std::filesystem::directory_entry &)> callback)
{
  if (!fs::exists(dirPath))
  {
    std::cerr << "Directory '" << dirPath << "' doesn't exist!\n";
    exit(0);
  }

  for (auto &entry : std::filesystem::recursive_directory_iterator{dirPath})
  {
    auto interupt = callback(entry);

    if (interupt)
    {
      return true;
    }
  }

  return false;
}

bool fs::walkr(path dirPath, std::function<bool(const std::filesystem::directory_entry &)> callback)
{
  return fs::walkRecursive(dirPath, callback);
}

std::vector<fs::path> fs::readDir(fs::path dirPath)
{
  std::vector<fs::path> paths;

  fs::walk(dirPath, [&](auto entry) -> bool
           { paths.push_back(entry); });

  return paths;
}

std::vector<fs::path> fs::ls(path dirPath)
{
  return fs::readDir(dirPath);
}

std::vector<fs::path> fs::dir(path dirPath)
{
  return fs::readDir(dirPath);
}

std::vector<fs::path> fs::readDirRecursive(fs::path dirPath)
{
  std::vector<fs::path> paths;

  fs::walkRecursive(dirPath, [&](auto entry) -> bool
                    { paths.push_back(entry); });

  return paths;
}

std::vector<fs::path> fs::lsr(path dirPath)
{
  return fs::readDirRecursive(dirPath);
}

std::vector<fs::path> fs::dirr(path dirPath)
{
  return fs::readDirRecursive(dirPath);
}
fs::File fs::open(path filePath, fs::openmode mode)
{
  return fs::File(filePath, mode);
}

bool fs::createDirectory(path dirPath)
{
  return std::filesystem::create_directories(dirPath);
}

bool fs::mkdir(path dirPath)
{
  return fs::createDirectory(dirPath);
}

bool fs::isDirectory(path filePath)
{
  return std::filesystem::is_directory(filePath);
}

bool fs::isEmpty(path filePath)
{
  return std::filesystem::is_empty(filePath);
}

bool fs::remove(path filePath)
{
  return std::filesystem::remove(filePath);
}

bool fs::rm(path filePath)
{
  return fs::remove(filePath);
}

bool fs::removeAll(path filePath)
{
  return std::filesystem::remove_all(filePath);
}

bool fs::rmrf(path filePath)
{
  return fs::removeAll(filePath);
}
void fs::move(path from, path to)
{
  std::filesystem::rename(from, to);
}

void fs::mv(path from, path to)
{
  fs::move(from, to);
}

void fs::copy(path from, path to)
{
  std::filesystem::copy(from, to, std::filesystem::copy_options::recursive);
}

void fs::cp(path from, path to)
{
  fs::copy(from, to);
}
