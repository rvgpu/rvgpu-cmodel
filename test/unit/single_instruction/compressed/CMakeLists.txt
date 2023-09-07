function(rvsim_ut_compress testname)
    rvsim_unit_test(rvsim_ut_compress_${testname} ut_${testname}.cpp)
endfunction()

rvsim_ut_compress(caddi)
rvsim_ut_compress(cjal)
rvsim_ut_compress(cli)
