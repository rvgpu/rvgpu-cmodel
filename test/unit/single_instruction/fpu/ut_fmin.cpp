#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fmin_d) {
    // 0x2a100053 : fmin.d f0, f0, f1
    double a = 1.1f;
    double b = 2.1f;
    test_instruction(0x2a100053, IN(reg::f0, a), IN(reg::f1, b), RES(reg::f0, a < b ? a : b));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fmin_s) {
    // 0x28100053 : fmin.s f0, f0, f1
    float a = 1.1f;
    float b = 2.1f;
    test_instruction(0x28100053, IN(reg::f0, a), IN(reg::f1, b), RES(reg::f0, a < b ? a : b));
}