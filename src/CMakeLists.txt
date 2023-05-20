
add_subdirectory(instructions)
add_subdirectory(common)
add_subdirectory(sm)

set(RVGSIM_FILES
        ${SM_FILES}
        ${INST_FILES}
        ${COMMON_FILES})

add_library(rvgsim SHARED ${RVGSIM_FILES})
set_target_properties(rvgsim PROPERTIES VERSION 0.0.1)
install(TARGETS rvgsim LIBRARY DESTINATION lib)
