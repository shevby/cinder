#include <string>
#include "catch2/catch_all.hpp"
#include "fs.h"
#include <iostream>
#include <algorithm>

const std::string TEST_OUTPUT_DIR{"@CMAKE_BINARY_DIR@/test"};
const std::string NAME_GEN_TEST_FILE = "test_fs.txt";
const std::filesystem::path NAME_TEST_DIR = "dirTest";
const std::string GEN_TEST_FILE_CONTENT = "FIRST LINE\nSECOND LINE\nTHIRD LINE";
const std::string NAME_TEST_FILE = "test.tmp.txt";

TEST_CASE("Test static functions")
{
  REQUIRE(fs::exists(NAME_GEN_TEST_FILE) == true);
  REQUIRE(fs::cwd() == TEST_OUTPUT_DIR);
  REQUIRE(fs::cwd() / "1" == fs::join("1"));
  REQUIRE(fs::readAll(fs::join(NAME_GEN_TEST_FILE)) == GEN_TEST_FILE_CONTENT);
  REQUIRE(fs::size(fs::join(NAME_GEN_TEST_FILE)) == GEN_TEST_FILE_CONTENT.size());

  std::vector<char> v(GEN_TEST_FILE_CONTENT.begin(), GEN_TEST_FILE_CONTENT.end());
  std::vector<char> vread = fs::readAllBytes(fs::join(NAME_GEN_TEST_FILE));

  REQUIRE(v.size() == vread.size());

  for (int i = 0; i < v.size(); i++)
  {
    REQUIRE(v[i] == vread[i]);
  }

  if (fs::exists(NAME_TEST_DIR))
  {
    fs::rmrf(NAME_TEST_DIR);
  }

  fs::mkdir(NAME_TEST_DIR / "1");
  fs::mkdir(NAME_TEST_DIR / "2/1");

  auto f = fs::open(NAME_TEST_DIR / "2/file.txt");
  f.close();

  std::vector<std::filesystem::path> paths1 = {NAME_TEST_DIR / "1", NAME_TEST_DIR / "2", NAME_TEST_DIR / "2/file.txt", NAME_TEST_DIR / "2/1"};
  std::sort(paths1.begin(), paths1.end());

  auto ls1 = fs::lsr(NAME_TEST_DIR);
  std::sort(ls1.begin(), ls1.end());

  REQUIRE(ls1.size() == paths1.size());

  for (int i = 0; i < paths1.size(); i++)
  {
    REQUIRE(ls1[i] == paths1[i]);
  }

  REQUIRE(fs::isDirectory(NAME_TEST_DIR) == true);
  REQUIRE(fs::isDirectory(NAME_TEST_DIR / "2/file.txt") == false);

  REQUIRE(fs::isEmpty(NAME_TEST_DIR / "1") == true);
  REQUIRE(fs::isEmpty(NAME_TEST_DIR) == false);
  REQUIRE(fs::isEmpty(NAME_TEST_DIR / "2/file.txt") == true);

  REQUIRE(fs::rm(NAME_TEST_DIR / "1") == true);
  REQUIRE(fs::rm(NAME_TEST_DIR / "2/file.txt") == true);

  std::vector<std::filesystem::path> paths2 = {NAME_TEST_DIR / "2", NAME_TEST_DIR / "2/1"};
  std::sort(paths2.begin(), paths2.end());
  auto ls2 = fs::lsr(NAME_TEST_DIR);

  std::sort(ls2.begin(), ls2.end());

  REQUIRE(ls2.size() == paths2.size());

  for (int i = 0; i < paths2.size(); i++)
  {
    REQUIRE(ls2[i] == paths2[i]);
  }

  auto f2 = fs::open(NAME_TEST_DIR / "2/file.txt");
  f2.close();

  fs::copy(NAME_TEST_DIR / "2", NAME_TEST_DIR / "1");
  fs::copy(NAME_TEST_DIR / "1/file.txt", NAME_TEST_DIR / "1/1");
  fs::copy(NAME_TEST_DIR / "2", NAME_TEST_DIR / "5");
  fs::mv(NAME_TEST_DIR / "5", NAME_TEST_DIR / "3");
  fs::mv(NAME_TEST_DIR / "3/file.txt", NAME_TEST_DIR / "file.txt");

  std::vector<std::filesystem::path> paths3 = {
      NAME_TEST_DIR / "1",
      NAME_TEST_DIR / "1/1",
      NAME_TEST_DIR / "1/file.txt",
      NAME_TEST_DIR / "1/1/file.txt",
      NAME_TEST_DIR / "2",
      NAME_TEST_DIR / "2/1",
      NAME_TEST_DIR / "2/file.txt",
      NAME_TEST_DIR / "3",
      NAME_TEST_DIR / "3/1",
      NAME_TEST_DIR / "file.txt"};

  std::sort(paths3.begin(), paths3.end());
  auto ls3 = fs::lsr(NAME_TEST_DIR);

  std::sort(ls3.begin(), ls3.end());

  REQUIRE(ls3.size() == paths3.size());

  for (int i = 0; i < paths3.size(); i++)
  {
    REQUIRE(ls3[i] == paths3[i]);
  }

  fs::mkdir(NAME_TEST_DIR / "4");
  fs::rm(NAME_TEST_DIR / "4");
  fs::rm(NAME_TEST_DIR / "file.txt");
  fs::rmrf(NAME_TEST_DIR / "1/1/file.txt");

  std::vector<std::filesystem::path> paths4 = {
      NAME_TEST_DIR / "1",
      NAME_TEST_DIR / "1/1",
      NAME_TEST_DIR / "1/file.txt",
      NAME_TEST_DIR / "2",
      NAME_TEST_DIR / "2/1",
      NAME_TEST_DIR / "2/file.txt",
      NAME_TEST_DIR / "3",
      NAME_TEST_DIR / "3/1"};

  std::sort(paths4.begin(), paths4.end());
  auto ls4 = fs::lsr(NAME_TEST_DIR);

  std::sort(ls4.begin(), ls4.end());

  REQUIRE(ls4.size() == paths4.size());

  for (int i = 0; i < paths4.size(); i++)
  {
    REQUIRE(ls4[i] == paths4[i]);
  }

  fs::rmrf(NAME_TEST_DIR);

  REQUIRE(!fs::exists(NAME_TEST_DIR));
}

TEST_CASE("Test File operations")
{

}