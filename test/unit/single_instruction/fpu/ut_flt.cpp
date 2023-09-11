#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_flt_d) {
    // 0xa2101553  flt.d a0, ft0, ft1
    test_instruction(0xa2101553, IN(reg::ft0, d2ul(double(1.1f))), IN(reg::ft1, d2ul(double(2.1f))), RES(reg::a0, 1));
    test_instruction(0xa2101553, IN(reg::ft0, d2ul(double(1.1f))), IN(reg::ft1, d2ul(double(1.1f))), RES(reg::a0, 0));
    test_instruction(0xa2101553, IN(reg::ft0, d2ul(double(2.1f))), IN(reg::ft1, d2ul(double(1.1f))), RES(reg::a0, 0));
}

TEST_F(ut_inst, decode_and_execute_rv64if_flt_s) {
    // 0xa0101553  flt.s a0, ft0, ft1
    test_instruction(0xa0101553, IN(reg::ft0, f2ul(float(1.1f))), IN(reg::ft1, f2ul(float(2.1f))), RES(reg::a0, 1));
    test_instruction(0xa0101553, IN(reg::ft0, f2ul(float(1.1f))), IN(reg::ft1, f2ul(float(1.1f))), RES(reg::a0, 0));
    test_instruction(0xa0101553, IN(reg::ft0, f2ul(float(2.1f))), IN(reg::ft1, f2ul(float(1.1f))), RES(reg::a0, 0));
}