set(
  LIB_SOURCES
  Map.cpp
)

add_library(${NAME_LIB_MAP} STATIC ${LIB_SOURCES})

include_directories(
  "./"
)