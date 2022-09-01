set(
  LIB_SOURCES
  "ResourceManager.cpp"
)

add_library(${NAME_LIB_RESOURCE_MANAGER} SHARED ${LIB_SOURCES})

target_link_libraries(
  ${NAME_LIB_RESOURCE_MANAGER} 
  PRIVATE
  sin
  ${NAME_LIB_FS}
 )