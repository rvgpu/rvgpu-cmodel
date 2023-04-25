project(RVGSIM)
cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD  11)
set(CMAKE_CXX_STANDARD 20)

set(project_top_path ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${project_top_path})

add_subdirectory(src)