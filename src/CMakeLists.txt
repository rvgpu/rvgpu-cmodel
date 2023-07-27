include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_compile_options(-fPIC)

add_subdirectory(common)
add_subdirectory(insns)
add_subdirectory(sm)
add_subdirectory(cp)
add_subdirectory(top)

# set(CMAKE_SHARED_LINKER_FLAGS "-fPIC")
add_library(rvgsim SHARED
        $<TARGET_OBJECTS:insns>
        $<TARGET_OBJECTS:sm>
        $<TARGET_OBJECTS:cp>
        $<TARGET_OBJECTS:top>)

set_target_properties(rvgsim PROPERTIES VERSION 0.0.1)
install(TARGETS rvgsim LIBRARY DESTINATION lib)
