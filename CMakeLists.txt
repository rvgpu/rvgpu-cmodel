cmake_minimum_required(VERSION 3.12)
project(RVGSIM)

set(CMAKE_C_STANDARD  11)
set(CMAKE_CXX_STANDARD 20)
set(project_top_path ${CMAKE_CURRENT_SOURCE_DIR})
set(project_binary_path ${CMAKE_BINARY_DIR})

add_subdirectory(softfloat)

enable_testing()
include(compile_options.cmake)
add_subdirectory(src)
add_subdirectory(libdrm)
add_subdirectory(test)
