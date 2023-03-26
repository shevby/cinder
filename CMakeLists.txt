cmake_minimum_required(VERSION 3.23)
project(Cinder VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

# Set Qt path
set(CMAKE_PREFIX_PATH "~/Qt/6.3.1/macos")

# Language config
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Outputs config
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(NAME_EXE_MAP_GENERATOR "mapgen")
set(NAME_LIB_MAP_GENERATOR "lmapgen")
set(NAME_LIB_MAP "lmap")
set(NAME_EXE_CCE "cce")
set(NAME_LIB_CINDER_ENGINE "cinderengine")
set(NAME_EXE_CINDER_MAIN "cinder")
set(NAME_LIB_FS "lfs")
set(NAME_EXE_RESOURCE_MANAGER "resman")
set(NAME_LIB_RESOURCE_MANAGER "lresman")

add_subdirectory("./src")

file(COPY "res" DESTINATION ${CMAKE_BINARY_DIR})