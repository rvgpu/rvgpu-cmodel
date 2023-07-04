function(rvsim_gen_insns_unittest testname)
    add_custom_command(
        OUTPUT ut_insns_gen_${testname}.cpp
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/general_insns_ut.py ${CMAKE_CURRENT_SOURCE_DIR} ${testname}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/general_insns_ut.py
    )

    rvsim_unit_test(ut_insns_gen_${testname})
endfunction()

rvsim_gen_insns_unittest(addi)
