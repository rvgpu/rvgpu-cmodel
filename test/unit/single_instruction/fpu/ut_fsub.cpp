#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fsub_d) {
    // 0x0a107053   fsub.d	ft0, ft0, ft1
    double a = 1.1f;
    double b = 2.1f;
    test_instruction(0x0a107053, IN(reg::ft0, a), IN(reg::ft1, b), RES(reg::ft0, a - b));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fsub_s) {
    // 0x08107053   fsub.s	ft0, ft0, ft1
    float a = 1.1f;
    float b = 2.1f;
    test_instruction(0x08107053, IN(reg::ft0, a), IN(reg::ft1, b), RES(reg::ft0, a - b));
}