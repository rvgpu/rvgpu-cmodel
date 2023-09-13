function(rvsim_ut_sim_framework testname)
    rvsim_unit_test(rvsim_ut_sim_framework_${testname} ut_${testname}.cpp)
endfunction()

rvsim_ut_sim_framework(interface)
