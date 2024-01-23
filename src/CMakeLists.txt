include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${project_top_path})
include(compile_options.cmake)

configure_file(top/librvgsim.pc.in librvgsim.pc @ONLY)

add_compile_options(-fPIC)

add_subdirectory(common)
add_subdirectory(rvcore)
add_subdirectory(sm)
add_subdirectory(simt)
add_subdirectory(cp)
add_subdirectory(vram)
add_subdirectory(mmu)
add_subdirectory(noc)
add_subdirectory(top)

# set(CMAKE_SHARED_LINKER_FLAGS "-fPIC")
add_library(rvgsim SHARED
        $<TARGET_OBJECTS:rvcore>
        $<TARGET_OBJECTS:sm>
        $<TARGET_OBJECTS:simt>
        $<TARGET_OBJECTS:cp>
        $<TARGET_OBJECTS:top>
        $<TARGET_OBJECTS:vram>
        $<TARGET_OBJECTS:mmu>
        $<TARGET_OBJECTS:noc>
        $<TARGET_OBJECTS:utils>)
target_link_libraries(rvgsim PRIVATE softfloat)

set_target_properties(rvgsim PROPERTIES VERSION 0.0.1)
install(TARGETS rvgsim LIBRARY DESTINATION lib)
install(FILES top/rvgsim.h DESTINATION include)
install(FILES top/command_stream.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/librvgsim.pc DESTINATION lib/pkgconfig)
