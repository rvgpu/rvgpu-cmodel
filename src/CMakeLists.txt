set(RVGSIM_FILES
        cu.cpp
        cu.h)
add_library(rvgsim SHARED ${RVGSIM_FILES})
set_target_properties(rvgsim PROPERTIES VERSION 0.0.1)
install(TARGETS rvgsim LIBRARY DESTINATION lib64)