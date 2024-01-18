function(rsim_ut testname)
    rvsim_unit_test(rsim_ut_${testname} ut_${testname}.cpp)
endfunction()

rsim_ut(cvt)