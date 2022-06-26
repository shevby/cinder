set(
  LIB_SOURCES
  "./Engine.cpp"
  "./Scene.cpp"
)

add_library(${NAME_LIB_CINDER_ENGINE} SHARED ${LIB_SOURCES})

target_link_libraries(
    ${NAME_LIB_CINDER_ENGINE}
    PRIVATE
    sfml-graphics
    sfml-system
    sfml-window
    sfml-audio
    ImGui-SFML::ImGui-SFML
)