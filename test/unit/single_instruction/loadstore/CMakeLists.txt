function(rvsim_ut_ls testname)
    rvsim_unit_test(rvsim_ut_ls_${testname} ut_${testname}.cpp)
endfunction()

rvsim_ut_ls(sb)
rvsim_ut_ls(sw)
rvsim_ut_ls(sd)
rvsim_ut_ls(flw)
rvsim_ut_ls(fsw)
rvsim_ut_ls(ld)
rvsim_ut_ls(lw)
rvsim_ut_ls(lwu)

