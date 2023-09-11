#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fnmsub_d) {
    // 0x2210724b   fnmsub.d ft4, ft0, ft1, ft4
    double a = 1.1f;
    double b = 2.1f;
    double c = 3.3f;
    test_instruction(0x2210724b, IN(reg::ft0, a), IN(reg::ft1, b), IN(reg::ft4, c), RES(reg::ft4, -(a * b - c)));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fnmsub_s) {
    // 0x2010724b   fnmsub.s ft4, ft0, ft1, ft4
    float a = 1.1f;
    float b = 2.1f;
    float c = 3.1f;
    test_instruction(0x2010724b, IN(reg::ft0, a), IN(reg::ft1, b), IN(reg::ft4, c), RES(reg::ft4, -(a * b - c)));
}
