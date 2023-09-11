function(rvsim_test_draw_basic testname)
    rvsim_test_draw(rvsim_test_draw_basic_${testname} ${testname}.cpp)
endfunction()

add_subdirectory(data)

rvsim_test_draw_basic(array)
rvsim_test_draw_basic(branch)
rvsim_test_draw_basic(vertex)
rvsim_test_draw_basic(triangle)
rvsim_test_draw_basic(matrix)
rvsim_test_draw_basic(math)