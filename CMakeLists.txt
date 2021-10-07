cmake_minimum_required(VERSION 3.5)

project(cinder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cinder main.cpp stable_random.cpp map.cpp)
