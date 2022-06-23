

set(
  LIB_SOURCES
  "MapGenerator.cpp"
  "PerlinNoise.cpp"
  "../Map/Map.cpp"
  "stable_random.cpp"
)

set(
  EXE_SOURCES
  "map_generator_cli.cpp"
  "arg_parser.cpp"
)

include_directories(
  "./"
  "../"
)

add_library(
  ${NAME_LIB_MAP_GENERATOR}
  SHARED
  ${LIB_SOURCES}
)

add_executable(
  ${NAME_EXE_MAP_GENERATOR}
  ${EXE_SOURCES}
)

target_link_libraries(${NAME_EXE_MAP_GENERATOR} PUBLIC ${NAME_LIB_MAP_GENERATOR})