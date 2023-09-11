#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fmul_d) {
    // 0x12b6f6d3 : fmul.d fa3, fa3, fa1
    double a = 1.1f;
    double b = 2.1f;
    test_instruction(0x12b6f6d3, IN(reg::fa3, a), IN(reg::fa1, b), RES(reg::fa3, a * b));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fmul_s) {
    // 0x10b6f6d3 : fmul.s fa3, fa3, fa1
    float a = 1.1f;
    float b = 2.1f;
    test_instruction(0x10b6f6d3, IN(reg::fa3, a), IN(reg::fa1, b), RES(reg::fa3, a * b));
}