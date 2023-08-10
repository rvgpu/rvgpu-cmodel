include_directories(${CMAKE_BINARY_DIR}/src)

add_subdirectory(alu)
add_subdirectory(fpu)
add_subdirectory(loadstore)
add_subdirectory(branch)