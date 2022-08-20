set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.3 REQUIRED COMPONENTS Quick Gui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt_add_executable(
  ${NAME_EXE_RESOURCE_MANAGER}
  main.cpp
)


set(
  QMLS
  "./qml/main.qml"
  "./qml/ControlPanel.qml"
  "./qml/ResourceTree.qml"
  "./qml/ResourceEditor.qml"
  )

qt_add_qml_module(
  ${NAME_EXE_RESOURCE_MANAGER}
  URI ui
  VERSION 1.0
  QML_FILES
  ${QMLS} 
)

target_link_libraries(${NAME_EXE_RESOURCE_MANAGER} PRIVATE Qt6::Gui Qt6::Quick)