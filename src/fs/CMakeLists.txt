set(
  SOURCES
  "./fs.cpp"
  "./File.cpp"
)

option(TEST_FS "Build catch2 tests" OFF)

# Language config
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(${TEST_FS})
  add_subdirectory("./test")
endif()


add_library(${NAME_LIB_FS} SHARED ${SOURCES})