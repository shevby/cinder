cmake_minimum_required(VERSION 3.5)

project(cinder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

set(SOURCES
    main.cpp
    stable_random.cpp
    map.cpp
    sin_parser.cpp
    perlin_noise.cpp
    arg_parser.cpp
    )


set(LIBS
    libs/sin
)



set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

add_executable(cinder ${SOURCES})

target_include_directories(cinder PUBLIC
    ${CMAKE_SOURCE_DIR}
    libs/
)

add_subdirectory(${LIBS})

target_link_libraries(cinder PUBLIC sin)

if(OpenMP_CXX_FOUND)
    target_link_libraries(cinder PUBLIC OpenMP::OpenMP_CXX)
endif()