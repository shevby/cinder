set(TEST_MAIN "test_fs")

set(
  TEST_SOURCES
  "${CMAKE_BINARY_DIR}/configured_files/test_fs.cpp"
)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

configure_file(
  "test_fs.cpp"
  "${CMAKE_BINARY_DIR}/configured_files/test_fs.cpp" ESCAPE_QUOTES
)

add_executable(${TEST_MAIN} ${TEST_SOURCES})
target_include_directories(${TEST_MAIN} PRIVATE "../")


target_link_libraries(
  ${TEST_MAIN}
  PRIVATE
  Catch2::Catch2WithMain
  ${NAME_LIB_FS}
)

set_target_properties(
  ${TEST_MAIN}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
)

file(COPY test_fs.txt DESTINATION "${CMAKE_BINARY_DIR}/test")