include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${project_top_path})

add_compile_options(-fPIC)

add_subdirectory(common)
add_subdirectory(rvcore)
add_subdirectory(sm)
add_subdirectory(sp)
add_subdirectory(cp)
add_subdirectory(top)

# set(CMAKE_SHARED_LINKER_FLAGS "-fPIC")
add_library(rvgsim SHARED
        $<TARGET_OBJECTS:rvcore>
        $<TARGET_OBJECTS:sm>
        $<TARGET_OBJECTS:sp>
        $<TARGET_OBJECTS:cp>
        $<TARGET_OBJECTS:top>
        $<TARGET_OBJECTS:utils>)
target_link_libraries(rvgsim PRIVATE softfloat)

set_target_properties(rvgsim PROPERTIES VERSION 0.0.1)
install(TARGETS rvgsim LIBRARY DESTINATION lib)
