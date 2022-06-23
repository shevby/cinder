
#Edit to update include directories
set(
  TARGET_DIRS
  "Map"
  "MapGenerator"
)

# Add all directories for include
include_directories(${TARGET_DIRS})

#Build targets
add_subdirectory("Map")
add_subdirectory("MapGenerator")