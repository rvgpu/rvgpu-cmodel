include_directories(${project_top_path}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/src)

add_subdirectory(sopp)
add_subdirectory(smem)