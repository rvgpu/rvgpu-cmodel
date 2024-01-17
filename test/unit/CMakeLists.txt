include_directories(${project_top_path}/src)
include_directories(${project_top_path}/test/unit)

function(rvsim_unit_test target testname)
    add_executable(${target} ${testname})
    target_link_libraries(${target} rvgsim gtest gtest_main)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

rvsim_unit_test(rvsim_gtest_framework gtest_framework.cpp)

if (RISCV)
    add_subdirectory(single_instruction)
else()
    add_subdirectory(rsingle_instruction)
endif ()

# add_subdirectory(insns_gen)
