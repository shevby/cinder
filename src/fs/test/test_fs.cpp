#include <string>
#include "catch2/catch_all.hpp"
#include "fs.h"
#include <iostream>

const std::string TEST_OUTPUT_DIR{"@CMAKE_BINARY_DIR@/test"};
const std::string TEST_FILE_NAME = "test_fs.txt";
const std::string TEST_FILE_CONTENT = "FIRST LINE\nSECOND LINE\nTHIRD LINE";

TEST_CASE("Test static functions")
{
  REQUIRE(fs::exists(TEST_FILE_NAME) == true);
  REQUIRE(fs::cwd() == TEST_OUTPUT_DIR);
  REQUIRE(fs::cwd() / "1" == fs::join("1"));
  REQUIRE(fs::readAll(fs::join(TEST_FILE_NAME)) == TEST_FILE_CONTENT);
  REQUIRE(fs::size(fs::join(TEST_FILE_NAME)) == TEST_FILE_CONTENT.size());

  std::vector<char> v(TEST_FILE_CONTENT.begin(), TEST_FILE_CONTENT.end());
  std::vector<char> vread = fs::readAllBytes(fs::join(TEST_FILE_NAME));

  REQUIRE(v.size() == vread.size());

  for (int i = 0; i < v.size(); i++)
  {
    REQUIRE(v[i] == vread[i]);
  }


}

TEST_CASE("Test File operations")
{

}