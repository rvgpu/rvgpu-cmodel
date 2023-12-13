cmake_minimum_required(VERSION 3.12)
project(RVGSIM)

set(CMAKE_C_STANDARD  11)
set(CMAKE_CXX_STANDARD 20)
set(project_top_path ${CMAKE_CURRENT_SOURCE_DIR})
set(project_binary_path ${CMAKE_BINARY_DIR})

set(BUILD_PACKAGE OFF)
if (BUILD_PACKAGE)
    set(PKG_INSTALL_DIR /usr/local/rvgpu)
else
    set(PKG_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
endif()

add_subdirectory(softfloat)

enable_testing()
add_subdirectory(src)
add_subdirectory(libdrm)
add_subdirectory(test)
