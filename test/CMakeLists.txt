set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

function(rvsim_unit_test testname)
    set(testcase ${testname})
    add_executable(${testcase} ${testname}.cpp)
    target_link_libraries(${testcase} rvgsim gtest gtest_main)
    target_include_directories(${testcase} PRIVATE ${project_top_path}/src)
    add_test(NAME ${testname} COMMAND ${testname})
endfunction()

add_subdirectory(unit)