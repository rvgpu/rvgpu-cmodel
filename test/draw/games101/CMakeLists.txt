function(rvsim_test_draw_games101 testname)
    rvsim_test_draw(rvsim_test_draw_games101_${testname} ${testname}.cpp)
endfunction()

add_subdirectory(data)

rvsim_test_draw_games101(games101_hw1)
rvsim_test_draw_games101(games101_hw2)
# rvsim_test_draw_games101(games101_hw3_texture_shader)
# rvsim_test_draw_games101(games101_hw3_normal_shader)
# rvsim_test_draw_games101(games101_hw3_phong_shader)
# rvsim_test_draw_games101(games101_hw3_bump_shader)
# rvsim_test_draw_games101(games101_hw3_displacement_shader)
rvsim_test_draw_games101(games101_hw4)