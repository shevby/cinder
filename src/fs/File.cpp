#include "File.h"

fs::File::File(path filePath, const openmode mode)
{
  file.open(filePath, mode);

  if (!file.is_open())
  {
    std::cerr << "Failed to open file '" << filePath << "'\n";
    exit(0);
  }
}

fs::File::~File()
{
  file.flush();
  file.close();
}

void fs::File::write(const std::string str)
{
  file << str;
}

void fs::File::write(const std::vector<char> buffer)
{
  file.write(&buffer[0], buffer.size());
}

void fs::File::write(const char *cstr)
{
  char *p = const_cast<char *>(cstr);

  while (*p != '\0')
  {
    p++;
  }

  size_t size = p - cstr;

  file.write(cstr, size);
}

void fs::File::write(const size_t size, const char *cbuffer)
{
  file.write(cbuffer, size);
}

std::string fs::File::File::readLine()
{
  std::string str;
  std::getline(file, str);

  return str;
}

void fs::File::read(std::vector<char> &buff, size_t size)
{
  if(buff.size() < size) {
    buff.resize(size);
  }

  file.read(&buff[0], size);
}

void fs::File::close()
{
  file.flush();
  file.close();
}

bool fs::File::eof() {
  return file.eof();    
}
