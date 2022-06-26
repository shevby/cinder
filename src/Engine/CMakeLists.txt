set(
  LIB_SOURCES
  "./Engine.cpp"
  "./Scene.cpp"
)

add_library(${NAME_LIB_CINDER_ENGINE} SHARED ${LIB_SOURCES})
