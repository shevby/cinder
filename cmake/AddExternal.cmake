set(SFML_VERSION "2.6.x")
set(SIN_VERSION "1.0.0")

function(addExternal)
  include(FetchContent)
  FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "${SFML_VERSION}"
  )
  FetchContent_GetProperties(sfml)

  FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.88
  )
  FetchContent_MakeAvailable(imgui)

  FetchContent_Declare(
    sin
    GIT_REPOSITORY https://github.com/shevby/sin
    GIT_TAG ${SIN_VERSION}
  )
  FetchContent_MakeAvailable(sin)

  FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml
    GIT_TAG 82dc2033e51b8323857c3ae1cf1f458b3a933c35
  )
  set(IMGUI_SFML_FIND_SFML OFF)
  set(IMGUI_DIR ${imgui_SOURCE_DIR})

  FetchContent_MakeAvailable(imgui-sfml)

  set(IMGUI_DIR ${imgui_SOURCE_DIR})

  if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    add_subdirectory(${imgui_SOURCE_DIR} ${imgui_BINARY_DIR})
  endif()

  if(NOT imgui-sfml_POPULATED)
    FetchContent_Populate(imgui-sfml)
    add_subdirectory(${imgui-sfml_SOURCE_DIR} ${imgui-sfml_BINARY_DIR})
  endif()

  if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
  endif()

  IF(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    INCLUDE_DIRECTORIES(/System/Library/Frameworks)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(GLUT_LIBRARY GLUT)
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
    MARK_AS_ADVANCED(COCOA_LIBRARY
      GLUT_LIBRARY
      OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY})
  ENDIF(APPLE)

  set_target_properties(
    sfml-audio
    PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
  )

  include_directories(
    "${sfml_SOURCE_DIR}/include"
    ${imgui_SOURCE_DIR}
    ${imgui-sfml_SOURCE_DIR}
    ${sin_SOURCE_DIR}
  )
endfunction(addExternal)
