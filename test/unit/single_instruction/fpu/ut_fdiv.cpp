#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fdiv_d) {
    // 0x1a20f0d3 : fdiv.d f1, f1, f2
    test_instruction(0x1a20f0d3, IN(reg::f1, double(1.1f)), IN(reg::f2, double(2.1f)), RES(reg::f1, double(1.1f) / double(2.1f)));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fdiv_s) {
    // 0x1820f0d3 : fdiv.s f1, f1, f2
    test_instruction(0x1820f0d3, IN(reg::f1, float(1.1f)), IN(reg::f2, float(2.1f)), RES(reg::f1, float(1.1f) / float(2.1f)));
}