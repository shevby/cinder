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
    void write(const std::string str);
    void write(const std::vector<char> buffer);
    void write(const char *cstr);
    void write(const size_t size, const char *cbuffer);
    std::string readLine();
    void read(std::vector<char> &buff, size_t size);
    void close();
  };
}