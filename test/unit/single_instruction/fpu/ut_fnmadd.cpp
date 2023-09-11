#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fnmadd_d) {
    // 0x0220f04f : fnmadd.d ft0, ft1, ft2, ft0
    double a = 1.1f;
    double b = 2.1f;
    double c = 3.1f;
    test_instruction(0x0220f04f, IN(reg::ft1, a), IN(reg::ft2, b), IN(reg::ft0, c), RES(reg::ft0, -(a * b + c)));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fnmadd_s) {
    // 0x0020f04f : fnmadd.s ft0, ft1, ft2, ft0
    float a = 1.1f;
    float b = 2.1f;
    float c = 3.1f;
    test_instruction(0x0020f04f, IN(reg::ft1, a), IN(reg::ft2, b), IN(reg::ft0, c), RES(reg::ft0, -(a * b + c)));
}