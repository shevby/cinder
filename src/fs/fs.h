#include "File.h"

namespace fs
{

  /**
   * @brief Check if file exists
   * 
   * @param filePath 
   * @return true if exists
   * @return false if not
   */
  bool exists(const path filePath);

  /**
   * @brief Returns current working directory
   * 
   * @return path 
   */
  path cwd();

  /**
   * @brief Joins filePath to current working directory
   * 
   * @param filePath path to join
   * @return path absolute path
   */
  path join(const path filePath);

  /**
   * @brief Reads all file content as string
   * 
   * @param filePath path to file
   * @return std::string file content
   */
  std::string readAll(const path filePath);

  /**
   * @brief Reads all file content as vector<char>
   * 
   * @param filePath path to file
   * @return std::vector<char> file content
   */
  std::vector<char> readAllBytes(const path filePath);

  /**
   * @brief Opens file with selected mode
   * 
   * @param filePath 
   * @param mode 
   * @return File 
   */
  fs::File open(path filePath, fs::openmode mode = fs::w | fs::r);

  /**
   * @brief Returns file size
   * 
   * @param filePath 
   * @return uintmax_t file size
   */
  uintmax_t size(const path filePath);

  /**
   * @brief Reads dir content
   * 
   * @param dirPath 
   * @return std::vector<path> dir content
   */
  std::vector<path> readDir(path dirPath = ".");
  std::vector<path> ls(path dirPath = ".");
  std::vector<path> dir(path dirPath = ".");

  /**
   * @brief Recursevly reads content in directory and subdirectories
   * 
   * @param dirPath 
   * @return std::vector<path> 
   */
  std::vector<path> readDirRecursive(path dirPath = ".");
  std::vector<path> lsr(path dirPath = ".");
  std::vector<path> dirr(path dirPath = ".");

  /**
   * @brief Walks through directory content and calls callback on every entry
   * 
   * @param dirPath directory to read
   * @param callback calback to call
   * @return true if walk was interupted by returning true from the callback
   * @return false if walk wasn't interupted
   */
  bool walk(path dirPath = ".", std::function<bool(const std::filesystem::directory_entry&)> callback);

    /**
   * @brief Recursebly walks through directory content and calls callback on every entry
   * 
   * @param dirPath directory to read
   * @param callback calback to call
   * @return true if walk was interupted by returning true from the callback
   * @return false if walk wasn't interupted
   */
  bool walkRecursive(path dirPath = ".", std::function<bool(const std::filesystem::directory_entry&)> callback);
  bool walkr(path dirPath = ".", std::function<bool(const std::filesystem::directory_entry&)> callback);
};