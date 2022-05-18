cmake_minimum_required(VERSION 3.5)

project(generate-map LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

set(SOURCES
    map_generator_cli.cpp
    stable_random.cpp
    MapGenerator.cpp
    perlin_noise.cpp
    arg_parser.cpp
    )

set(HEADERS
    MapGenerator.h
    stable_random.h
    perlin_noise.h
    arg_parser.h
    constants.h
    )


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

add_executable(generate-map ${SOURCES} ${HEADERS})

if(OpenMP_CXX_FOUND)
    target_link_libraries(generate-map PUBLIC OpenMP::OpenMP_CXX)
endif()
