#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fclass_d) {
    // 0xe2001553 : fclass.d a0, f0
    test_instruction(0xe2001553, IN(reg::f0, d2ul(double(1.1))), RES(reg::a0, 1 << 6));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fclass_s) {
    // 0xe0001553 : fclass.s a0, f0
    test_instruction(0xe0001553, IN(reg::f0, f2ul(float(1.1))), RES(reg::a0, 1 << 6));
}