cmake_minimum_required(VERSION 3.12)
project(RVGSIM)

set(CMAKE_C_STANDARD  11)
set(CMAKE_CXX_STANDARD 20)

include(compile_options.cmake)
enable_testing()

set(project_top_path ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${project_top_path})
include_directories(${project_top_path}/src)

add_subdirectory(src)
add_subdirectory(libdrm)
add_subdirectory(test)
