#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fle_d) {
    // 0xa2100553  fle.d a0, ft0, ft1
    test_instruction(0xa2100553, IN(reg::ft0, d2ul(double(1.1f))), IN(reg::ft1, d2ul(double(2.1f))), RES(reg::a0, 1));
    test_instruction(0xa2100553, IN(reg::ft0, d2ul(double(1.1f))), IN(reg::ft1, d2ul(double(1.1f))), RES(reg::a0, 1));
    test_instruction(0xa2100553, IN(reg::ft0, d2ul(double(2.1f))), IN(reg::ft1, d2ul(double(1.1f))), RES(reg::a0, 0));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fle_s) {
    // 0xa0100553  fle.s a0, ft0, ft1
    test_instruction(0xa0100553, IN(reg::ft0, f2ul(float(1.1f))), IN(reg::ft1, f2ul(float(2.1f))), RES(reg::a0, 1));
    test_instruction(0xa0100553, IN(reg::ft0, f2ul(float(1.1f))), IN(reg::ft1, f2ul(float(1.1f))), RES(reg::a0, 1));
    test_instruction(0xa0100553, IN(reg::ft0, f2ul(float(2.1f))), IN(reg::ft1, f2ul(float(1.1f))), RES(reg::a0, 0));
}