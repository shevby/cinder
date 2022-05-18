cmake_minimum_required(VERSION 3.5)

project(CinderCellEditor LANGUAGES CXX)

set(VERSION 0.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    ResourceManager.cpp
    CinderCellEditor.cpp
    Item.cpp
    CinderMap.cpp
    Controls.cpp
    switch.cpp
    Cursor.cpp
    Overlay.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    imgui-sfml/imgui-SFML.cpp
    )


set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/bin/sfml/include")
set(IMGUI_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/imgui")
set(IMGUI_SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/imgui-sfml")


set(SFML_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/bin/sfml/lib")

IF(APPLE)
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(GLUT_LIBRARY GLUT )
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    MARK_AS_ADVANCED (COCOA_LIBRARY
                      GLUT_LIBRARY
                      OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY})
ENDIF (APPLE)

IF (UNIX AND NOT APPLE)
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lGL -lGLU -lGLEW -lglut")
ENDIF (UNIX AND NOT APPLE)

link_directories(${SFML_LIBRARY_DIR})
include_directories(
    ${SFML_INCLUDE_DIR} 
    ${IMGUI_INCLUDE_DIR} 
    ${IMGUI_SFML_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
    )

add_executable(cce ${SOURCES})

target_link_libraries (cce sfml-graphics sfml-window sfml-system ${EXTRA_LIBS})

add_compile_definitions(VERSION="${VERSION}")

# Resources
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
