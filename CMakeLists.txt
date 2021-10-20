cmake_minimum_required(VERSION 3.5)

project(cinder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    stable_random.cpp
    map.cpp
    sin_parser.cpp
    perlin_noise.cpp
    arg_parser.cpp
    )

set(HEADERS
    map.h
    stable_random.h
    sin_parser.h
    perlin_noise.h
    arg_parser.h
    )

add_executable(cinder ${SOURCES} ${HEADERS})
