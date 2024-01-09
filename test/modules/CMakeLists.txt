include_directories(${project_top_path})

function(rvsim_modules_ut testname)
    set(target rvsim_modules_${testname})
    add_executable(${target} ut_${testname}.cpp)
    target_link_libraries(${target} modules gtest gtest_main)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

rvsim_modules_ut(interface)
rvsim_modules_ut(module)
