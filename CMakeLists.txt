cmake_minimum_required(VERSION 3.12)
project(RVGSIM)

set(CMAKE_C_STANDARD  11)
set(CMAKE_CXX_STANDARD 20)
set(project_top_path ${CMAKE_CURRENT_SOURCE_DIR})
set(project_binary_path ${CMAKE_BINARY_DIR})

if (BUILD_PACKAGE)
    set(PACKAGE_INSTALL_DIR /usr/local/rvgpu)
else()
    set(PACKAGE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
endif()

enable_testing()

add_subdirectory(softfloat)
add_subdirectory(modules)

add_subdirectory(src)
add_subdirectory(libdrm)
# add_subdirectory(test)
