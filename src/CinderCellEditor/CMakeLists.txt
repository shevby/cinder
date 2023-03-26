set(
    SOURCES
    "./main.cpp"
    "./CinderCellEditor.cpp"
    "./CinderMap.cpp"
    "./Controls.cpp"
    "./Cursor.cpp"
    "./Item.cpp"
    "./Overlay.cpp"
    "./ResourceManager.cpp"
    "./switch.cpp"
)

add_executable(${NAME_EXE_CCE} ${SOURCES})

target_link_libraries(
    ${NAME_EXE_CCE}
    PRIVATE
    sfml-graphics
    sfml-system
    sfml-window
    sfml-audio
    ImGui-SFML::ImGui-SFML
)