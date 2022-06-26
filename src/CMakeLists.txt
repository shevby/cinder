
#Edit to update include directories
set(
  TARGET_DIRS
  "Map"
  "MapGenerator"
  "CinderCellEditor"
  "Engine"
  "Cinder"
)

# Add all directories for include
include_directories(${TARGET_DIRS})

#Build targets
add_subdirectory("Map")
add_subdirectory("MapGenerator")
add_subdirectory("CinderCellEditor")
add_subdirectory("Engine")
add_subdirectory("Cinder")