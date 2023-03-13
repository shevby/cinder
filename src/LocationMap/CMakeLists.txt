project("Location Map")
cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (
    LIB_SOURCES
    LocationMapStateCache.cpp
    LocationMapStateShort.cpp
    Gzip.cpp
    webserver.cpp
    Server.cpp
    HttpRequest.cpp
    location_map_poc.cpp
    utils.cpp
    JsonConfig.cpp
)

include_directories (
    "./"
)

add_library (
    "LocationMap"
    SHARED
    ${LIB_SOURCES}
)

add_executable (
    "LocationMapMain"
    "LocationMapMain.cpp"
)

target_link_libraries (
    "LocationMapMain"
    PUBLIC
    "LocationMap"
)

target_link_libraries(
    "LocationMapMain"
    PRIVATE
    Threads::Threads
)

add_executable (
    "test_location_map"
    "test_location_map.cpp"
)

target_link_libraries (
    "test_location_map"
    PUBLIC
    "LocationMap"
)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.0.1
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries (
    "test_location_map"
    PRIVATE
    Catch2::Catch2WithMain
)

