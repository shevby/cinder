set(
  SORUCES
  "./main.cpp"
)

add_executable(${NAME_EXE_CINDER_MAIN} ${SORUCES})
target_link_libraries(${NAME_EXE_CINDER_MAIN} PUBLIC ${NAME_LIB_CINDER_ENGINE})