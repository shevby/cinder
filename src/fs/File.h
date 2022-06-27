#pragma once

#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <functional>

namespace fs
{
  typedef std::ios::openmode openmode;
  typedef std::filesystem::path path;

  
  enum class openmodes
  {
    w = std::ios::out,
    r = std::ios::in,
    b = std::ios::binary,
    a = std::ios::app
  };

  const openmode w = std::ios::out;
  const openmode r = std::ios::in;
  const openmode b = std::ios::binary;
  const openmode a = std::ios::app;

  class File
  {
  private:
  std::fstream file;

  public:
    File(std::filesystem::path path, const openmode mode = w | r);
    virtual ~File();
    /**
     * @brief Writes string to file
     * 
     * @param str 
     */
    void write(const std::string str);

    /**
     * @brief Writes vector<char> to file
     * 
     * @param buffer 
     */
    void write(const std::vector<char> buffer);

    /**
     * @brief Writes C string to file (must to end with '\0')
     * 
     * @param cstr 
     */
    void write(const char *cstr);

    /**
     * @brief Writes C buffer to file
     * 
     * @param size size to write
     * @param cbuffer pointer to buffer
     */
    void write(const size_t size, const char *cbuffer);

    /**
     * @brief Reads file line
     * 
     * @return std::string 
     */
    std::string readLine();

    /**
     * @brief Reads defined amount (size) of bytes to the buffer (buff)
     * 
     * @param buff buffer to write, if size is not enough will be resized automatically.
     * @param size size to read
     */
    void read(std::vector<char> &buff, size_t size);

    /**
     * @brief Closes file.
     * 
     */
    void close();

    /**
     * @brief End of file. Checks if file is ended
     * 
     * @return true 
     * @return false 
     */
    bool eof();
  };
}